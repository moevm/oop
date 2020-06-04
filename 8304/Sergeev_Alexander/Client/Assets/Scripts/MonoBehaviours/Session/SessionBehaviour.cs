using System.Collections.Generic;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using GuiConcreteComponents;
using JsonSchemas;
using JsonSchemas.Generators;
using Singletons;
using UnityEngine;


namespace MonoBehaviours.Session
{
    public class SessionBehaviour : MonoBehaviour
    {
        private static SessionBehaviour _instance;

        private string _sessionName;
        private States _state;
        private List<int> _playersUid;

        private void Awake()
        {
            _instance = this;
            _sessionName = null;
            _state = States.choosing;
            _playersUid = null;
        }
        
        private void Start()
        {
            God.NetworkManager.Send(new in_session_info());
        }

        private void Update()
        {
            
        }
        
        private void OnDestroy()
        {
            _instance = null;
        }
        
        public static void SetSessionName(string sessionName)
        {
            if (!_instance) return;
            _instance._sessionName = sessionName;
        }
        
        public static void SetState(string state)
        {
            if (!_instance) return;
            if (state == _instance._state.ToString()) return;
            switch (state)
            {
                case "choosing":
                    _instance._state = States.choosing;
                    break;
                case "holding":
                    _instance._state = States.holding;
                    break;
                case "playing":
                    _instance._state = States.playing;
                    break;
                default:
                    MessageBox.Error($"Unknown state: {state}");
                    break;
            }
            God.NetworkManager.Send(new in_session_info());
            God.NetworkManager.Send(new in_game_info());
        }

        public static void SetPlayers(List<int> players_uid)
        {
            if (!_instance) return;
            _instance._playersUid = players_uid;
        }

        public static List<int> GetPlayers()
        {
            if (!_instance) return null;
            return _instance._playersUid;
        }
    }
}