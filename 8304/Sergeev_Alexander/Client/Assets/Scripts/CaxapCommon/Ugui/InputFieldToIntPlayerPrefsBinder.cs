using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using TMPro;
using UnityEngine;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Synchronizes PlayerPrefs int with InputField
    /// </summary>
    [ExecuteAlways]
    public class InputFieldToIntPlayerPrefsBinder : MonoBehaviour
    {
        public IntPrefs Key;

        private TMP_InputField _inputField;

        public void Awake()
        {
            _inputField = GetComponent<TMP_InputField>();
            _inputField.characterValidation = TMP_InputField.CharacterValidation.Integer;
            _inputField.onValueChanged.AddListener(InputFieldValueChanged);
            PlayerPrefsWrapper.IntPrefsChanged += PrefsChanged;
        }

        [ContextMenu("Reset")]
        private void Start()
        {
            _inputField.text = int.TryParse(_inputField.text, out int result) ? PlayerPrefsWrapper.Get(Key, result).ToString() : PlayerPrefsWrapper.Get(Key).ToString();
            PlayerPrefsWrapper.Set(Key, int.Parse(_inputField.text));
        }

        private void InputFieldValueChanged(string data)
        {
            if (int.TryParse(data, out int result))
            {
                PlayerPrefsWrapper.Set(Key, result);
            }
        }

        private void PrefsChanged(object sender, (IntPrefs, int) data)
        {
            if (data.Item1 == Key) _inputField.text = data.Item2.ToString();
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.IntPrefsChanged -= PrefsChanged;
        }
    }
}