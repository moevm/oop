using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;


namespace CaxapCommon.Preferences
{
    /// <summary>
    /// Loads specified scene when KeyShouldExist becomes not 0
    /// </summary>
    public class SceneLoaderOnPlayerPrefs : MonoBehaviour
    {
        public Scenes SceneName;
        public IntPrefs KeyShouldExist;

        private void Awake()
        {
            PlayerPrefsWrapper.IntPrefsChanged += ValueChanged;
        }
        
        private void ValueChanged(object sender, (IntPrefs, int) data)
        {
            if (data.Item1 == KeyShouldExist && data.Item2 != 0) UnityWrapper.LoadScene(SceneName);
        }

        private void OnDestroy()
        {
            PlayerPrefsWrapper.IntPrefsChanged -= ValueChanged;
        }
    }
}