using System.Collections.Generic;
using JsonSchemas;
using JsonSchemas.Structs;
using Singletons;
using UnityEngine;
using UnityEngine.UI;


namespace GuiConcreteComponents.Session
{
    public class ChatScrollList : MonoBehaviour
    {
        public ChatScrollListItem ItemPrefab;

        private RectTransform _contentTransform;

        private static ChatScrollList _instance;

        private void Awake()
        {
            _instance = this;
            _contentTransform = GetComponent<ScrollRect>().content;
        }

        private void Start()
        {
            God.NetworkManager.Send(new in_read_chat());
        }

        public static void DrawScrollList(List<chat_message> messages)
        {
            if (!_instance) return;
            foreach (Transform child in _instance._contentTransform.transform)
            {
                Destroy(child.gameObject);
            }
            foreach (chat_message message in messages)
            {
                Instantiate(_instance.ItemPrefab, _instance._contentTransform).VisualizeData(message);
            }
        }

        private void OnDestroy()
        {
            _instance = null;
        }
    }
}