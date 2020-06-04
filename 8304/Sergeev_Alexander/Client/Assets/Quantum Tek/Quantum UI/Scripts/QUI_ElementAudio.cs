using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_ElementAudio is used to make UI sounds on an element.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Element Audio")]
    [DisallowMultipleComponent]
    [RequireComponent(typeof(AudioSource))]
    public class QUI_ElementAudio : MonoBehaviour
    {
        [Header("Object References")]
        [Tooltip("The AudioSource to play sounds from.")]
        public AudioSource audioSource;
        [Tooltip("The audio preset to get sounds from.")]
        public QUI_ElementAudioPreset audioPreset;

        /// <summary>
        /// Plays an audio clip from the audio preset.
        /// </summary>
        /// <param name="name"></param>
        public void Play(string name)
        {
            foreach (var clip in audioPreset.clips)
            {
                if (clip.name == name && clip.clip)
                {
                    audioSource.PlayOneShot(clip.clip, clip.volume);
                    break;
                }
            }
        }
    }
}