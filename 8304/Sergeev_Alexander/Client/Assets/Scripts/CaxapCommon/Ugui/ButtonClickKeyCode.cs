using UnityEngine;
using UnityEngine.UI;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Clicks button on keyboard press KeyCode (only when button is interactable)
    /// </summary>
    public class ButtonClickKeyCode : MonoBehaviour
    {
        public KeyCode ClickCode;

        private Button _button;
        
        private void Awake()
        {
            _button = GetComponent<Button>();
        }

        private void Update()
        {
            if (!_button.interactable) return;
            if (Input.GetKeyDown(ClickCode)) _button.onClick.Invoke();
        }
    }
}