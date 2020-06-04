using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;


namespace CaxapCommon.Preferences
{
    /// <summary>
    /// Sends message when KeyShouldExist becomes not empty and set in to empty
    /// </summary>
    public class RequestOnStringPlayerPrefs : MonoBehaviour
    {
        public Requests Request;
        public StrPrefs KeyShouldExist;
        
        private void Awake()
        {
            PlayerPrefsWrapper.StringPrefsChanged += ValueChanged;
        }

        private void Start()
        {
            if (PlayerPrefsWrapper.Get(KeyShouldExist) != "")
            {
                UnityWrapper.GetRequestMethod(Request).Invoke();
                PlayerPrefsWrapper.Take(KeyShouldExist);
            };
        }

        private void ValueChanged(object sender, (StrPrefs, string) data)
        {
            if (data.Item1 == KeyShouldExist && data.Item2 != "")
            {
                UnityWrapper.GetRequestMethod(Request).Invoke();
                PlayerPrefsWrapper.Take(KeyShouldExist);
            }
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.StringPrefsChanged -= ValueChanged;
        }
    }
}