using System.Collections.Generic;
using JsonSchemas;
using JsonSchemas.Online;
using MonoBehaviours;
using Singletons;
using UnityEngine;
using UnityEngine.UI;


namespace GuiConcreteComponents.Lobby
{
    public class SessionScrollList : MonoBehaviour
    {
        public SessionScrollListItem ItemPrefab;

        private static SessionScrollList _instance;
        private RectTransform _contentTransform;
        private Dictionary<int, out_session_info> _sessions;
        private float _lastUpdateTime;

        private void Awake()
        {
            _instance = this;
            _contentTransform = GetComponent<ScrollRect>().content;
            _sessions = null;
            _lastUpdateTime = Time.time;
        }

        private void Start()
        {
            UpdateData();
        }

        private void Update()
        {
            if (Time.time - _lastUpdateTime > Constants.SlowUpdateDelay)
            {
                _lastUpdateTime = Time.time;
                UpdateData();
            }
        }
        
        private void OnDestroy()
        {
            _instance = null;
        }

        public static void UpdateData()
        {
            God.NetworkManager.Send(new in_server_info());
        }

        public static void DrawScrollList(Dictionary<int, out_session_info> sessions)
        {
            if (!_instance) return;
            _instance._sessions = sessions;
            foreach (Transform child in _instance._contentTransform.transform)
            {
                Destroy(child.gameObject);
            }
            foreach (KeyValuePair<int, out_session_info> session in sessions)
            {
                Instantiate(_instance.ItemPrefab, _instance._contentTransform).VisualizeData(session.Key, session.Value.session);
            }
        }

        public static session GetSessionById(int id)
        {
            if (!_instance || _instance._sessions == null || !_instance._sessions.ContainsKey(id)) return null;
            return _instance._sessions[id].session;
        }
    }
}