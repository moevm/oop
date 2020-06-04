using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using TMPro;
using UnityEngine;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Synchronizes PlayerPrefs string with Text
    /// </summary>
    [ExecuteAlways]
    public class TextToStringPlayerPrefsBinder : MonoBehaviour
    {
        public StrPrefs Key;

        private TMP_Text _text;

        public void Awake()
        {
            _text = GetComponent<TMP_Text>();
            PlayerPrefsWrapper.StringPrefsChanged += PrefsChanged;
        }

        [ContextMenu("Reset")]
        private void Start()
        {
            _text.text = PlayerPrefsWrapper.Get(Key, _text.text);
        }

        private void PrefsChanged(object sender, (StrPrefs, string) data)
        {
            if (data.Item1 == Key) _text.text = data.Item2;
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.StringPrefsChanged -= PrefsChanged;
        }
    }
}