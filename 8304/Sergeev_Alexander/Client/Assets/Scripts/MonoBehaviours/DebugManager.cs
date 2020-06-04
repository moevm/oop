using System;
using System.Net;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using GuiConcreteComponents;
using JsonSchemas;
using NativeWebSocket;
using Singletons;
using UnityEngine;


namespace MonoBehaviours
{
    public class DebugManager : MonoBehaviour
    {
        public AudioSource Geiger;

        private void Awake()
        {
            Geiger = GetComponent<AudioSource>();
        }


        private WebSocket websocket;
        private void Start()
        {
            /*//ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;
            //ServicePointManager.ServerCertificateValidationCallback = delegate { return true; };
            //websocket = new WebSocket("wss://163.172.163.152:1109");
            //websocket = new WebSocket("wss://nahui.me:1108");
            websocket = new WebSocket("wss://nahui.me:1109");
            //websocket = new WebSocket("wss://worldofbeat.com:1108");
            //websocket = new WebSocket("wss://worldofbeat.com:1109");
            //websocket = new WebSocket("wss://echo.websocket.org");

            websocket.OnOpen += () =>
            {
                Debug.Log("Connection open!");
            };

            websocket.OnError += (e) =>
            {
                Debug.Log("Error! " + e);
            };

            websocket.OnClose += (e) =>
            {
                Debug.Log("Connection closed!");
            };

            websocket.OnMessage += (bytes) =>
            {
                Debug.Log("OnMessage!");
                Debug.Log(bytes);

                // getting the message as a string
                // var message = System.Text.Encoding.UTF8.GetString(bytes);
                // Debug.Log("OnMessage! " + message);
            };
            // waiting for messages
            
            await websocket.Connect();*/
        }
        
        private void OnApplicationQuit()
        {
            //await websocket.Close();
        }

        public void Update ()
        {
            if (Input.GetKeyDown(KeyCode.P) && Input.GetKey(KeyCode.Tab))
            {
                MessageBox.Info($"PlayerPrefs:\n"
                    + $"{StrPrefs.input_message.ToString()} {PlayerPrefsWrapper.Get(StrPrefs.input_message)}\n"
                    + $"{StrPrefs.input_nickname.ToString()} {PlayerPrefsWrapper.Get(StrPrefs.input_nickname)}\n"
                    + $"{StrPrefs.server_ip.ToString()} {PlayerPrefsWrapper.Get(StrPrefs.server_ip)}\n"
                    + $"{StrPrefs.input_session_name.ToString()} {PlayerPrefsWrapper.Get(StrPrefs.input_session_name)}\n"
                    + $"{IntPrefs.chat_buffer_updates.ToString()} {PlayerPrefsWrapper.Get(IntPrefs.chat_buffer_updates)}\n"
                    + $"{IntPrefs.sender.ToString()} {PlayerPrefsWrapper.Get(IntPrefs.sender)}\n"
                    + $"{IntPrefs.session_id.ToString()} {PlayerPrefsWrapper.Get(IntPrefs.session_id)}\n");
            }
            
            if (Input.GetKeyDown(KeyCode.F12) && Input.GetKey(KeyCode.F2))
            {
                PlayerPrefs.DeleteAll();
            }

            if (Input.GetKeyDown(KeyCode.U) && Input.GetKey(KeyCode.Tab))
            {
                God.NetworkManager.Send(new in_game_info());
            }
            
            if (Input.GetKeyDown(KeyCode.L) && Input.GetKey(KeyCode.Tab))
            {
                PlayerPrefsWrapper.Set(StrPrefs.server_ip, Constants.IpLocalhost);
                God.NetworkManager.ConnectToServer();
            }
        }

        public void PlayShot()
        {
            Geiger.Play();
        }

        [ContextMenu("Clear Player Prefs")]
        public void ClearPlayerPrefs()
        {
            PlayerPrefs.DeleteAll();
        }
    }
}
