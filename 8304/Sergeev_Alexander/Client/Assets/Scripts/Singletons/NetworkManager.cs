using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using GuiConcreteComponents;
using JsonSchemas;
using NativeWebSocket;
using UnityEngine;


namespace Singletons
{
    public class NetworkManager : MonoBehaviour
    {
        public WebSocket Ws = null; // Ws is working on another thread! 
        public ConcurrentQueue<string> EventQueue;
        public List<string> Users;

        private void Awake()
        {
            EventQueue = new ConcurrentQueue<string>();
        }

        private void Start()
        {
            ConnectToServer();
        }

        private void Update()
        {
            if (!EventQueue.IsEmpty)
            {
                if (EventQueue.TryDequeue(out string result))
                {
                    //Debug.Log("Will Try " + result + "|||");
                    j_typed response = JsonManager.Deserialize(result);
                    Debug.Log("Try " + result + "|||" + JsonManager.Serialize(response));
                    response.Execute();
                }
            }
        }

        private async void OnDestroy()
        {
            if (God.NetworkManager == this && IsConnected()) await Ws.Close();
        }

        public void ConnectToServer()
        {
            if (IsConnected()) return;
            string ip = PlayerPrefsWrapper.Get(StrPrefs.server_ip);
            try
            {
                Ws = new WebSocket($"wss://{ip}");
            }
            catch (Exception e)
            {
                MessageBox.Error($"WebSocketFactory exception: {e.Message}");
                return;
            }
            Ws.OnOpen += WsOnOpen;
            Ws.OnMessage += WsOnMessage;
            Ws.OnError += WsOnError;
            Ws.OnClose += WsOnClose;
            Task.Run(() => Ws.Connect());
        }

        public bool IsConnected()
        {
            return Ws != null && Ws.State == WebSocketState.Open;
        }

        public void Send(j_typed data)
        {
            if (!data.IsValid())
            {
                Debug.LogWarning($"Data isn't valid: {JsonManager.Serialize(data)}");
                return;
            }
            Send(JsonManager.Serialize(data));
        }

        public void Send(string message)
        {
            if (!IsConnected())
            {
                MessageBox.Error($"You are not connected (trying to send {message})");
                return;
            }
            Debug.Log($"Sending {message}");
            Task.Run(() => SendAsync(message));
        }

        private async void SendAsync(string message)
        {
            await Ws.SendText(message);
        }

        public string GetUsernameById(int playerId)
        {
            if (playerId < 0) return $"LOG {playerId}";
            if (God.NetworkManager.Users.Count <= playerId)
            {
                Send(new in_connect());
                return playerId.ToString(); // TODO
            }
            return God.NetworkManager.Users[playerId];
        }

        private void WsOnOpen()
        {
            Debug.Log("WS opened");
        }

        private void WsOnMessage(byte[] data)
        {
            string message = Encoding.UTF8.GetString(data);
            EventQueue.Enqueue(message);
        }

        private void WsOnError(string errMsg)
        {
            MessageBox.Error($"WebSocket error: {errMsg}");
        }

        private void WsOnClose(WebSocketCloseCode code)
        {
            MessageBox.Info($"WebSocket closed with code: {code}");
        }
    }
}