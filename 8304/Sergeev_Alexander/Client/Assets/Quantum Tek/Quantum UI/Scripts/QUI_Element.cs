using UnityEngine;
using UnityEngine.Events;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_Element is the base for most UI elements in the Quantum UI system. It contains all the basic fields and methods used by each element.
    /// </summary>
    public abstract class QUI_Element : MonoBehaviour
    {
        [Tooltip("If the element should start as active. Keep in mind only one tab window can be active, if this is a tab window.")]
        public bool startActive = true;
        [Tooltip("The animation name from the animation preset on the element animator to play at the start if active.")]
        [SerializeField] private string startActiveAnimation = "Active";
        [Tooltip("The animation name from the animation preset on the element animator to play at the start if inactive.")]
        [SerializeField] private string startInactiveAnimation = "Inactive";
        [HideInInspector] public bool active;

        [Header("Element Object References")]
        [Tooltip("The animator to use, if there is one.")]
        public QUI_ElementAnimator animator;
        [Tooltip("The audio to use, if there is one.")]
        public new QUI_ElementAudio audio;

        [Header("Element Events")]
        [Tooltip("Invoked when the element is activated.")]
        public UnityEvent onActive;
        [Tooltip("Invoked when the element is deactivated.")]
        public UnityEvent onInactive;

        public virtual void Start()
        {
            SetActive(startActive);

            if (animator)
                animator.PlayAnimation(active ? startActiveAnimation : startInactiveAnimation, 1);
        }

        /// <summary>
        /// Changes the active state of the element.
        /// </summary>
        /// <param name="value"></param>
        public virtual void SetActive(bool value)
        {
            bool oldActive = active;
            active = value;

            if (oldActive != active)
            {
                if (active)
                    onActive.Invoke();
                else
                    onInactive.Invoke();
            }
        }

        /// <summary>
        /// Plays an audio clip with the given name from the element audio preset.
        /// </summary>
        /// <param name="name"></param>
        public void PlayAudio(string name)
        {
            if (!audio)
                return;

            audio.Play(name);
        }
    }
}