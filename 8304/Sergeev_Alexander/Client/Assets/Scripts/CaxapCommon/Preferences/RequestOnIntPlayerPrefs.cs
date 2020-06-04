using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;


namespace CaxapCommon.Preferences
{
    /// <summary>
    /// Sends message when KeyShouldExist becomes not 0 and set in to 0
    /// </summary>
    public class RequestOnIntPlayerPrefs : MonoBehaviour
    {
        public Requests Request;
        public IntPrefs KeyShouldExist;
        
        private void Awake()
        {
            PlayerPrefsWrapper.IntPrefsChanged += ValueChanged;
        }

        private void Start()
        {
            if (PlayerPrefsWrapper.Get(KeyShouldExist) != 0)
            {
                UnityWrapper.GetRequestMethod(Request).Invoke();
                PlayerPrefsWrapper.Take(KeyShouldExist);
            };
        }

        private void ValueChanged(object sender, (IntPrefs, int) data)
        {
            if (data.Item1 == KeyShouldExist && data.Item2 != 0)
            {
                UnityWrapper.GetRequestMethod(Request).Invoke();
                PlayerPrefsWrapper.Take(KeyShouldExist);
            }
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.IntPrefsChanged -= ValueChanged;
        }
    }
}