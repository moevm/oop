using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;
using UnityEngine.UI;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Button is interactable only when KeyShouldExist isn't 0
    /// </summary>
    [ExecuteAlways]
    public class ButtonToIntPlayerPrefsBinder : MonoBehaviour
    {
        public Requests Request;
        public IntPrefs KeyShouldExist;

        private Button _button;
        
        public void Awake()
        {
            _button = GetComponent<Button>();
            _button.onClick.AddListener(UnityWrapper.GetRequestMethod(Request));
            PlayerPrefsWrapper.IntPrefsChanged += ValueChanged;
        }

        [ContextMenu("Reset")]
        private void Start()
        {
            _button.interactable = PlayerPrefsWrapper.Get(KeyShouldExist) != 0;
        }

        private void ValueChanged(object sender, (IntPrefs, int) data)
        {
            if (data.Item1 == KeyShouldExist) _button.interactable = data.Item2 != 0;
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.IntPrefsChanged -= ValueChanged;
        }
    }
}