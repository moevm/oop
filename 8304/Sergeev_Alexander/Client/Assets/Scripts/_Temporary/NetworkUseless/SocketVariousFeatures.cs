using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;


namespace NetworkUseless
{
    // https://metanit.com/sharp/net/3.1.php
    public static class SocketVariousFeatures
    {
        public static Socket TcpSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        public static Socket UdpSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

        public static void CreateTcpSocketServer(string ip, int port)
        {
            // получаем адреса для запуска сокета
            IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(ip), port);

            // создаем сокет
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                // связываем сокет с локальной точкой, по которой будем принимать данные
                socket.Bind(ipPoint);

                // начинаем прослушивание
                // Метод Listen вызывается только после метода Bind.
                // В качестве параметра он принимает количество входящих подключений,
                // которые могут быть поставлены в очередь сокета.
                socket.Listen(10);

                Console.WriteLine("Сервер запущен. Ожидание подключений...");
                while (true)
                {
                    // После вызова метода Listen начинается прослушивание
                    // входящих подключений, и если подключения приходят на сокет,
                    // то их можно получить с помощью метода Accept
                    // Метод Accept извлекает из очереди ожидающих запрос первый запрос
                    // и создает для его обработки объект Socket.
                    // Если очередь запросов пуста, то метод Accept блокирует
                    // вызывающий поток до появления нового подключения.
                    Socket handler = socket.Accept();

                    // получаем сообщение
                    StringBuilder builder = new StringBuilder();
                    int bytes = 0; // количество полученных байтов
                    byte[] data = new byte[256]; // буфер для получаемых данных

                    do
                    {
                        // Метод Receive в качестве параметра принимает массив байтов,
                        // в который считываются полученные данные,
                        // и возвращает количество полученных байтов.
                        bytes = handler.Receive(data);
                        builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    } while (handler.Available > 0);

                    Console.WriteLine(DateTime.Now.ToShortTimeString() + ": " + builder.ToString());

                    // отправляем ответ
                    string message = "ваше сообщение доставлено";
                    data = Encoding.Unicode.GetBytes(message);

                    // После получения данных клиенту посылается ответное сообщение
                    // с помощью метода Send, который в качестве параметра
                    // принимает массив байтов:
                    handler.Send(data);

                    // В конце обработки запроса надо закрыть связанный с ним сокет:
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public static void CreateTcpSocketClient(string ip, int port)
        {
            try
            {
                IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(ip), port);
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                // Для клиента характерно все то же самое,
                // только теперь после создания сокета вызывается метод Connect(),
                // в который передается адрес сервера:
                socket.Connect(ipPoint);

                // -Temp-
                Console.Write("Введите сообщение:");
                string message = Console.ReadLine();

                // -----

                byte[] data = Encoding.Unicode.GetBytes(message);
                socket.Send(data);

                // получаем ответ
                data = new byte[256]; // буфер для ответа
                StringBuilder builder = new StringBuilder();
                int bytes = 0; // количество полученных байт

                do
                {
                    bytes = socket.Receive(data, data.Length, 0);
                    builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                } while (socket.Available > 0);
                Console.WriteLine("ответ сервера: " + builder.ToString());

                // закрываем сокет
                socket.Shutdown(SocketShutdown.Both);
                socket.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.Read();
        }

        // Протокол UDP не требует установки постоянного подключения,
        // и, возможно, многим покажется легче работать с UDP, чем с TCP.
        // Большинство принципов при работе с UDP те же, что и с TCP.

        public static void CreateUdpSocket(string localIp, int localPort, string remoteIp, int remotePort)
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Udp);
            try
            {
                // прослушивание 
                Task listeningTask = new Task(() => { Listen(socket, localIp, localPort); });
                listeningTask.Start();

                // отправка сообщений
                while (true)
                {
                    string message = Console.ReadLine();

                    byte[] data = Encoding.Unicode.GetBytes(message);
                    EndPoint remotePoint = new IPEndPoint(IPAddress.Parse(remoteIp), remotePort);
                    socket.SendTo(data, remotePoint);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                // закрытие сокета
                if (socket != null)
                {
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                    socket = null;
                }
            }
        }

        // поток для приема подключений
        private static void Listen(Socket socket, string localIp, int localPort)
        {
            try
            {
                //Прослушиваем по адресу
                IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(localIp), localPort);
                socket.Bind(ipPoint);

                while (true)
                {
                    // получаем сообщение
                    StringBuilder builder = new StringBuilder();
                    int bytes = 0; // количество полученных байтов
                    byte[] data = new byte[256]; // буфер для получаемых данных

                    //адрес, с которого пришли данные
                    EndPoint remoteIp = new IPEndPoint(IPAddress.Any, 0);

                    do
                    {
                        bytes = socket.ReceiveFrom(data, ref remoteIp);
                        builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    } while (socket.Available > 0);

                    // получаем данные о подключении
                    IPEndPoint remoteFullIp = remoteIp as IPEndPoint;

                    // выводим сообщение
                    Console.WriteLine("{0}:{1} - {2}", remoteFullIp.Address.ToString(), remoteFullIp.Port,
                        builder.ToString());
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                // закрытие сокета
                if (socket != null)
                {
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                    socket = null;
                }
            }
        }
    }
}