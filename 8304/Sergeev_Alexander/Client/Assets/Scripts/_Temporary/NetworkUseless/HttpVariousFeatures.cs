using System;
using System.IO;
using System.Net;
using System.Threading.Tasks;


namespace NetworkUseless
{
    // https://metanit.com/sharp/net/2.1.php
    public static class NetworkVariousFeatures
    {
        // IPAddress ip = IPAddress.Parse("127.0.0.1");

        public static IPHostEntry GetIpHostEntry(string domain)
        {
            IPHostEntry host = Dns.GetHostEntry(domain);

            // host.HostName
            // host.AddressList
            return host;
        }

        public static void DownloadFile(string url, string path)
        {
            WebClient client = new WebClient();
            client.DownloadFile(url, path);
        }

        public static async Task DownloadFileAsync(string url, string path)
        {
            WebClient client = new WebClient();
            await client.DownloadFileTaskAsync(new Uri(url), path);
        }

        public static async Task GetRequestAsync(string url, string getData)
        {
            try
            {
                WebRequest request = WebRequest.Create($"{url}?{getData}");
                WebResponse response = await request.GetResponseAsync();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        Console.WriteLine(reader.ReadToEnd());
                    }
                }
                response.Close();
            }
            catch (WebException e)
            {
                // получаем статус исключения
                WebExceptionStatus status = e.Status;

                if (status == WebExceptionStatus.ProtocolError)
                {
                    HttpWebResponse httpResponse = (HttpWebResponse)e.Response;
                    Console.WriteLine("Статусный код ошибки: {0} - {1}",
                        (int)httpResponse.StatusCode, httpResponse.StatusCode);
                }
            }
        }

        public static async Task PostRequestAsync(string url, string postData)
        {
            try
            {
                WebRequest request = WebRequest.Create(url);
                request.Method = "POST";

                // данные для отправки
                string data = postData; // Example: "sName=Иван Иванов&age=31"

                // преобразуем данные в массив байтов
                byte[] byteArray = System.Text.Encoding.UTF8.GetBytes(data);

                // устанавливаем тип содержимого - параметр ContentType
                request.ContentType = "application/x-www-form-urlencoded";

                // Устанавливаем заголовок Content-Length запроса - свойство ContentLength
                request.ContentLength = byteArray.Length;

                //записываем данные в поток запроса
                using (Stream dataStream = request.GetRequestStream())
                {
                    dataStream.Write(byteArray, 0, byteArray.Length);
                }

                WebResponse response = await request.GetResponseAsync();
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        Console.WriteLine(reader.ReadToEnd());
                    }
                }
                response.Close();
            }
            catch (WebException e)
            {
                // получаем статус исключения
                WebExceptionStatus status = e.Status;

                if (status == WebExceptionStatus.ProtocolError)
                {
                    HttpWebResponse httpResponse = (HttpWebResponse)e.Response;
                    Console.WriteLine("Статусный код ошибки: {0} - {1}",
                        (int)httpResponse.StatusCode, httpResponse.StatusCode);
                }
            }
        }
    }
}