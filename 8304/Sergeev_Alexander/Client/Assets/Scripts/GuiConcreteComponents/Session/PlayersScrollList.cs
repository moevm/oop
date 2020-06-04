using System.Collections.Generic;
using JsonSchemas.Structs;
using TMPro;
using UnityEngine;
using UnityEngine.UI;


namespace GuiConcreteComponents.Session
{
    public class PlayersScrollList : MonoBehaviour
    {
        public PlayersScrollListItem ItemPrefab;
        public TMP_Text HeaderText;

        private RectTransform _contentTransform;

        private static PlayersScrollList _instance;

        private void Awake()
        {
            _instance = this;
            _contentTransform = GetComponent<ScrollRect>().content;
        }

        private void Start()
        {
            
        }
        
        public static void DrawScrollList(List<int> players)
        {
            if (!_instance) return;
            _instance.HeaderText.text = "Users";
            foreach (Transform child in _instance._contentTransform.transform)
            {
                Destroy(child.gameObject);
            }
            foreach (int uid in players)
            {
                Instantiate(_instance.ItemPrefab, _instance._contentTransform).VisualizeData(uid);
            }
        }

        public static void DrawScrollList(Dictionary<int, player> players)
        {
            if (!_instance) return;
            _instance.HeaderText.text = "Players";
            foreach (Transform child in _instance._contentTransform.transform)
            {
                Destroy(child.gameObject);
            }
            foreach (KeyValuePair<int, player> player in players)
            {
                Instantiate(_instance.ItemPrefab, _instance._contentTransform).VisualizeData(player.Key, player.Value);
            }
        }

        private void OnDestroy()
        {
            _instance = null;
        }
    }
}