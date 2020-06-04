using System.Collections.Generic;
using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using UnityEngine;


namespace CaxapCommon.Preferences
{
    /// <summary>
    /// Removes specified prefs on awake
    /// </summary>
    public class PrefsCleaner : MonoBehaviour
    {
        public List<StrPrefs> StrPrefsesToClean;
        public List<IntPrefs> IntPrefsesToClean;

        private void Awake()
        {
            foreach (StrPrefs prefs in StrPrefsesToClean)
            {
                PlayerPrefsWrapper.Take(prefs);
            }
            foreach (IntPrefs prefs in IntPrefsesToClean)
            {
                PlayerPrefsWrapper.Take(prefs);
            }
        }
    }
}