using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    public Text playText;
    public Text controlText;
    public Text settingText;
    public Text exitText;

    private void Start()
    {
        playText.text = "PLAY";
        controlText.text = "CONTROLS";
        settingText.text = "CREDITS";
        exitText.text = "EXIT";
    }

    public void QuitGame()
    {
        Application.Quit();
    }

    public void PlayCredits()
    {
        SceneManager.LoadScene("Credits");
    }
}
