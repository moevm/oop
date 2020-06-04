using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;
using UnityEngine.UI;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Load SceneName scene on click
    /// </summary>
    public class ButtonSceneLoader : MonoBehaviour
    {
        public Scenes SceneName;
        
        private Button _button;

        private void Awake()
        {
            _button = GetComponent<Button>();
            _button.onClick.AddListener(OnButtonClicked);
        }

        private void OnButtonClicked()
        {
            UnityWrapper.LoadScene(SceneName);
        }

        private void OnDestroy()
        {
            _button.onClick.RemoveListener(OnButtonClicked);
        }
    }
}