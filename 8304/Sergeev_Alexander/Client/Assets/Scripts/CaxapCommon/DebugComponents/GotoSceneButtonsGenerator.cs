using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


namespace CaxapCommon.DebugComponents
{
    public class GotoSceneButtonsGenerator : MonoBehaviour
    {
        public Button ButtonPrefab;
        public RectTransform ContentTransform;
    
        private void Start()
        {
            for (int i = 0; i < SceneManager.sceneCount; i++)
            {
                string sceneName = SceneManager.GetSceneAt(i).name;
                Button button = Instantiate(ButtonPrefab, Vector3.zero, Quaternion.identity, ContentTransform);
                button.name = sceneName;
                button.GetComponentInChildren<Text>().text = sceneName;
                button.onClick.AddListener(() => SceneManager.LoadScene(sceneName));
            }
        }
    }
}