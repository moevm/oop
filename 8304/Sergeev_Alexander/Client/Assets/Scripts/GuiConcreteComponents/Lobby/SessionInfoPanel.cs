using System.Collections.Generic;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using JsonSchemas;
using JsonSchemas.Online;
using JsonSchemas.Structs;
using MonoBehaviours;
using Singletons;
using TMPro;
using UnityEngine;


namespace GuiConcreteComponents.Lobby
{
    public class SessionInfoPanel : MonoBehaviour
    {
        public TMP_Text SessionName;
        public TMP_Text SessionData; // TODO

        private static SessionInfoPanel _instance;

        private float _lastUpdateTime;

        private void Awake()
        {
            _instance = this;
            _lastUpdateTime = Time.time;
            PlayerPrefsWrapper.IntPrefsChanged += PrefsChanged;
        }

        private void PrefsChanged(object sender, (IntPrefs, int) data)
        {
            //if (data.Item1 == IntPrefs.session_id) God.NetworkManager.Send(new in_session_info());
        }

        private void Start()
        {
            ClearPanel();
        }

        private void Update()
        {
            if (Time.time - _lastUpdateTime > Constants.SlowUpdateDelay)
            {
                _lastUpdateTime = Time.time;
                God.NetworkManager.Send(new in_session_info());
            }
        }

        private void ClearPanel()
        {
            SessionName.text = "Choose session";
            SessionData.text = "Welcome to the lobby.\nThis client is based on Unity, server is based on node.js, logic is based on C++. If you have any problems, try to restart the game and press F2+F12 buttons at the same time. This will remove cached data. Make sure to take screenshot and send it to me when you see strange game behaviour!\nHave fun ;)";
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.IntPrefsChanged -= PrefsChanged;
            _instance = null;
        }

        public static void DrawPanel(session current)
        {
            if (!_instance) return;
            if (current == null)
            {
                _instance.ClearPanel();
                return;
            }
            _instance.SessionName.text = current.session_name;
            // FIXME
            _instance.SessionData.text = "";
            if (current.state != null)
            {
                _instance.SessionData.text += $"State: {current.state}\n";
            }
            if (current.players_uid != null)
            {
                _instance.SessionData.text += $"Accounts:\n";
                foreach (int i in current.players_uid)
                {
                    _instance.SessionData.text += $"{i} - {God.NetworkManager.GetUsernameById(i)}\n";
                }
            }
            if (current.game != null)
            {
                _instance.SessionData.text += "Users\n";
                foreach (KeyValuePair<int, player> player in current.game.players)
                {
                    _instance.SessionData.text += $"{God.NetworkManager.GetUsernameById(player.Key)} team: {player.Value.team}\n";
                }
                //_instance.SessionData.text += current.game.tilemap.GetData();
            }
            // FIXME
        }
    }
}