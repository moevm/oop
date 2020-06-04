using System;
using CaxapCommon.Enums;
using UnityEngine;


namespace CaxapCommon.Wrappers
{
    public static class PlayerPrefsWrapper
    {
        public static event EventHandler<(StrPrefs, string)> StringPrefsChanged;

        public static event EventHandler<(IntPrefs, int)> IntPrefsChanged;

        public static string Get(StrPrefs stringType, string defaultData = "")
        {
            return PlayerPrefs.GetString(stringType.ToString(), defaultData);
        }

        public static int Get(IntPrefs intType, int defaultData = 0)
        {
            return PlayerPrefs.GetInt(intType.ToString(), defaultData);
        }

        public static void Set(StrPrefs stringType, string data)
        {
            PlayerPrefs.SetString(stringType.ToString(), data);
            StringPrefsChanged?.Invoke(null, (stringType, data));
        }

        public static void Set(IntPrefs intType, int data)
        {
            PlayerPrefs.SetInt(intType.ToString(), data);
            IntPrefsChanged?.Invoke(null, (intType, data));
        }

        public static string Take(StrPrefs stringType)
        {
            string data = Get(stringType);
            Set(stringType, "");
            return data;
        }

        public static int Take(IntPrefs intType)
        {
            int data = Get(intType);
            Set(intType, 0);
            return data;
        }
    }
}