using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class beerpongstartbuttons : MonoBehaviour {
   
    public void PlayButton() {
        Debug.Log("Start Button was pressed");
        SceneManager.LoadScene("Environment");
    }

    public void QuitButton() {
        Application.Quit();
    }

    public void CreditsButton()
    {
        SceneManager.LoadScene("Credits");
    }

    public void MainMenuButton()
    {
        SceneManager.LoadScene("beerpongstartmenu");
    }
}
