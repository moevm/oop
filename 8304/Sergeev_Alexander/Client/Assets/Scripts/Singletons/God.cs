using CaxapCommon.Enums;
using CaxapCommon.Wrappers;
using MonoBehaviours;
using UnityEngine;


namespace Singletons
{
    public class God : MonoBehaviour
    {
        public static God I = null;
        public static NetworkManager NetworkManager;
        public static DebugManager DebugManager;

        private void Awake()
        {
            if (I)
            {
                Destroy(gameObject);
                return;
            }
            DontDestroyOnLoad(gameObject);
            I = this;
            NetworkManager = GetComponent<NetworkManager>();
            DebugManager = GetComponent<DebugManager>();
            SetupClient();
        }

        private void SetupClient()
        {
            PlayerPrefsWrapper.Set(StrPrefs.server_ip, Constants.Ip);
        }
    }
}