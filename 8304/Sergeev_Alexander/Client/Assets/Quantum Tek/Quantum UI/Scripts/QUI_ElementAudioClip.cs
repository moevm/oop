using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_ElementAudioClip stores info about an audio clip to be played an element audio source.
    /// </summary>
    [System.Serializable]
    public class QUI_ElementAudioClip
    {
        public string name;
        public AudioClip clip;
        public float volume = 1;
    }
}