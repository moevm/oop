using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using TMPro;
using UnityEngine;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Synchronizes PlayerPrefs string with InputField
    /// </summary>
    [ExecuteAlways]
    public class InputFieldToStringPlayerPrefsBinder : MonoBehaviour
    {
        public StrPrefs Key;

        private TMP_InputField _inputField;

        public void Awake()
        {
            _inputField = GetComponent<TMP_InputField>();
            _inputField.onValueChanged.AddListener(InputFieldValueChanged);
            PlayerPrefsWrapper.StringPrefsChanged += PrefsChanged;
        }

        [ContextMenu("Reset")]
        private void Start()
        {
            _inputField.text = PlayerPrefsWrapper.Get(Key, _inputField.text);
            PlayerPrefsWrapper.Set(Key, _inputField.text);
        }

        private void InputFieldValueChanged(string text)
        {
            PlayerPrefsWrapper.Set(Key, text);
        }

        private void PrefsChanged(object sender, (StrPrefs, string) data)
        {
            if (data.Item1 == Key) _inputField.text = data.Item2;
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.StringPrefsChanged -= PrefsChanged;
        }
    }
}