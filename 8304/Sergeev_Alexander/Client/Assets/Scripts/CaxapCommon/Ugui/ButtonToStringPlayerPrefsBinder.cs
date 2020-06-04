using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;
using UnityEngine.UI;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Button is interactable only when KeyShouldExist isn't empty
    /// </summary>
    [ExecuteAlways]
    public class ButtonToStringPlayerPrefsBinder : MonoBehaviour
    {
        public StrPrefs KeyShouldExist;
        public Requests Request;

        private Button _button;
        
        public void Awake()
        {
            _button = GetComponent<Button>();
            _button.onClick.AddListener(UnityWrapper.GetRequestMethod(Request));
            PlayerPrefsWrapper.StringPrefsChanged += ValueChanged;
        }

        [ContextMenu("Reset")]
        private void Start()
        {
            _button.interactable = PlayerPrefsWrapper.Get(KeyShouldExist) != "";
        }

        private void ValueChanged(object sender, (StrPrefs, string) data)
        {
            if (data.Item1 == KeyShouldExist) _button.interactable = data.Item2 != "";
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.StringPrefsChanged -= ValueChanged;
        }
    }
}