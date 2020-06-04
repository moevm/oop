using System;
using CaxapCommon.Enums;
using JsonSchemas;
using Singletons;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;


namespace CaxapCommon.Wrappers
{
    public static class UnityWrapper
    {
        public static void LoadScene(Scenes sceneName)
        {
            PlayerPrefs.Save();
            SceneManager.LoadScene(sceneName.ToString());
        }
        
        public static UnityAction GetRequestMethod(Requests request)
        {
            switch (request)
            {
                case Requests.in_connect:
                    return () => God.NetworkManager.Send(new in_connect());
                case Requests.in_server_info:
                    return () => God.NetworkManager.Send(new in_server_info());
                case Requests.in_read_chat:
                    return () => God.NetworkManager.Send(new in_read_chat());
                case Requests.in_write_chat:
                    return () => God.NetworkManager.Send(new in_write_chat());
                case Requests.in_create_session:
                    return () => God.NetworkManager.Send(new in_create_session());
                case Requests.in_session_info:
                    return () => God.NetworkManager.Send(new in_session_info());
                case Requests.in_game_info:
                    return () => God.NetworkManager.Send(new in_game_info());
                case Requests.in_game_load:
                    return () => God.NetworkManager.Send(new in_game_load());
                case Requests.in_game_save:
                    return () => God.NetworkManager.Send(new in_game_save());
                case Requests.in_game_join:
                    return () => God.NetworkManager.Send(new in_game_join());
                case Requests.in_game_quit:
                    return () => God.NetworkManager.Send(new in_game_quit());
                case Requests.in_game_play:
                    return () => God.NetworkManager.Send(new in_game_play());
                case Requests.in_game_pause:
                    return () => God.NetworkManager.Send(new in_game_pause());
                case Requests.in_game_stop:
                    return () => God.NetworkManager.Send(new in_game_stop());
                case Requests.in_game_setup:
                    return () => God.NetworkManager.Send(new in_game_setup());
                case Requests.in_game_signal:
                    throw new NotImplementedException("In game signal cant send on button");
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }
    }
}