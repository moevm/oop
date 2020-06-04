using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace QuantumTek.QuantumUI
{
    /// <summary>
    /// QUI_LoadType determines how a scene should be loaded.
    /// </summary>
    [System.Serializable]
    public enum QUI_LoadType
    {
        /// <summary> The scene will load instantly, with transition effects. </summary>
        Instant,
        /// <summary> The scene will load asynchronously (in the background), while showing some loading UI after the start of the scene transition effect. </summary>
        LoadingUI,
        /// <summary> The scene will load asynchronously (in the background), while showing a loading scene. </summary>
        LoadingScene
    }

    /// <summary>
    /// QUI_SceneTransition handles smooth transition effects between scenes, along with loading screen effects.
    /// </summary>
    [AddComponentMenu("Quantum Tek/Quantum UI/Scene Transition")]
    [DisallowMultipleComponent]
    public class QUI_SceneTransition : MonoBehaviour
    {
        [Header("Scene Transition Object References")]
        [Tooltip("The animator used in running the scene transition.")]
        public QUI_ElementAnimator animator;
        [Tooltip("The loading bar to update, if there is one.")]
        public QUI_Bar loadingBar;
        [Tooltip("The UI element to show when loading, if there is one.")]
        public RectTransform loadingUI;

        [Header("Scene Transition Variables")]
        [Tooltip("How to load the scene.")]
        public QUI_LoadType loadType;
        public static string sceneToLoad = "";
        [Tooltip("The name of the loading scene, if the type is LoadingScene.")]
        public string loadingSceneName = "";
        [Tooltip("The name of the transition animation to play when entering a scene.")]
        public string enterSceneAnimation;
        [Tooltip("The name of the transition animation to play when exiting a scene.")]
        public string exitSceneAnimation;

        private void Awake()
        {
            if (sceneToLoad.Length > 0)
            {
                if (SceneManager.GetActiveScene().name == sceneToLoad)
                {
                    sceneToLoad = "";

                    if (animator)
                        animator.PlayAnimation(enterSceneAnimation);
                }

                if (loadType == QUI_LoadType.LoadingScene && SceneManager.GetActiveScene().name == loadingSceneName)
                    StartLoad();
            }
        }

        /// <summary>
        /// Starts to load the necessary scene, used at the end of scene transition animations.
        /// </summary>
        public void StartLoad()
        {
            if (sceneToLoad.Length == 0)
                return;
            if (loadType == QUI_LoadType.LoadingUI || (loadType == QUI_LoadType.LoadingScene && SceneManager.GetActiveScene().name == loadingSceneName))
                StartCoroutine(LoadSceneAsync(sceneToLoad));
            else if (loadType == QUI_LoadType.LoadingScene && SceneManager.GetActiveScene().name != sceneToLoad)
                SceneManager.LoadScene(loadingSceneName);
        }

        /// <summary>
        /// Starts loading a scene, with behaviour based on the loading type.
        /// </summary>
        /// <param name="sceneName"></param>
        public void LoadScene(string sceneName)
        {
            if (loadType == QUI_LoadType.Instant)
                SceneManager.LoadScene(sceneName);
            else if (loadType == QUI_LoadType.LoadingUI)
            {
                sceneToLoad = sceneName;
                if (loadingUI)
                    loadingUI.gameObject.SetActive(true);

                if (animator)
                    animator.PlayAnimation(exitSceneAnimation);
            }
            else if (loadType == QUI_LoadType.LoadingScene)
            {
                sceneToLoad = sceneName;

                if (animator)
                    animator.PlayAnimation(exitSceneAnimation);
            }
        }

        protected IEnumerator LoadSceneAsync(string sceneName)
        {
            AsyncOperation loadOperation = SceneManager.LoadSceneAsync(sceneName);

            while (!loadOperation.isDone)
            {
                float loadProgress = Mathf.Clamp01(loadOperation.progress / 0.9f);

                if (loadingBar)
                    loadingBar.SetFill(loadProgress);

                yield return null;
            }
        }
    }
}