using UnityEngine;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_ElementAnimator is used to handle animation of a UI element.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Element Animator")]
    [DisallowMultipleComponent]
    [RequireComponent(typeof(Animator))]
    public class QUI_ElementAnimator : MonoBehaviour
    {
        [Header("Object References")]
        [Tooltip("The animator component to use.")]
        public Animator animator;
        [Tooltip("The animation preset to use when animating this element.")]
        public QUI_ElementAnimationPreset animationPreset;

        public void PlayAnimation(QUI_ElementAnimation animation, float normalizedTime)
        {
            if (!animator.gameObject.activeSelf
                || (animator.transform.parent && !animator.transform.parent.gameObject.activeSelf)
                || (animator.transform.parent.parent && !animator.transform.parent.parent.gameObject.activeSelf)) return;

            animation.Play(animator, normalizedTime);
        }
        public void PlayAnimation(QUI_ElementAnimation animation)
        {
            if (!animator.gameObject.activeSelf
                || (animator.transform.parent && !animator.transform.parent.gameObject.activeSelf)
                || (animator.transform.parent.parent && !animator.transform.parent.parent.gameObject.activeSelf)) return;

            animation.Play(animator);
        }
        public void PlayAnimation(string name, float normalizedTime)
        {
            foreach (var animation in animationPreset.animations)
            {
                if (animation.name == name)
                {
                    PlayAnimation(animation, normalizedTime);
                    break;
                }
            }
        }
        /// <summary>
        /// Plays an animation from the preset, by the given name.
        /// </summary>
        /// <param name="name"></param>
        public void PlayAnimation(string name)
        {
            PlayAnimation(name, 0);
        }
    }
}