using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SettingMenu : MonoBehaviour
{
    public Text settingText;
    public Text volumeText;
    public Text backText;

    private void Awake()
    {
        settingText.text = "SETTINGS";
        volumeText.text = "VOLUME";
        backText.text = "BACK";
    }
}
