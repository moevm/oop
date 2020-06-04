using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;


namespace GuiConcreteComponents
{
    public class MessageBox : MonoBehaviour
    {
        public GameObject ContentObject;
        public TMP_Text HeaderText;
        public TMP_Text DataText;
        public Button OkButton;

        private static MessageBox _instance;
        private static Queue<(string, string)> _messageQueue;
        private Vector2 _startMousePosition;
        private Vector2 _startMessageBoxPosition;

        private void Awake()
        {
            _instance = this;
            if (_messageQueue == null) _messageQueue = new Queue<(string, string)>();
            OkButton.onClick.AddListener(OnButtonClick);
        }

        private void Update()
        {
            if (_messageQueue.Count > 0 && !ContentObject.activeSelf)
            {
                Show(_messageQueue.Dequeue());
            }
        }
        
        public static void Info(string message)
        {
            if (_instance == null)
            {
                return;
            }
            _instance.AddMessage("INFO", message);
        }
        
        public static void Error(string message)
        {
            if (_instance == null)
            {
                return;
            }
            _instance.AddMessage("ERROR", message);
        }

        private void OnButtonClick()
        {
            ContentObject.SetActive(false);
        }

        private void AddMessage(string header, string message)
        {
            _messageQueue.Enqueue((header, message));
        }

        private void Show((string, string) message)
        {
            HeaderText.text = message.Item1;
            DataText.text = message.Item2;
            ContentObject.SetActive(true);
        }

        private void OnDestroy()
        {
            if (ContentObject.activeSelf)
            {
                _messageQueue.Enqueue((HeaderText.text, DataText.text));
            }
            _instance = null;
        }
    }
}