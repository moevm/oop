using UnityEngine;
using UnityEngine.UI;


namespace CaxapCommon.Ugui
{
    /// <summary>
    /// Change GameObject.activeSelf on click
    /// </summary>
    public class ButtonSetActive : MonoBehaviour
    {
        public GameObject Content;

        private void Awake()
        {
            GetComponent<Button>().onClick.AddListener(OnButtonClick);
        }

        private void OnButtonClick()
        {
            Content.SetActive(!Content.activeSelf);
        }
    }
}