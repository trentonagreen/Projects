﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EndGame : MonoBehaviour
{
    public void Restart()
    {
        SceneManager.LoadScene("Environment");
    }

    public void MainMenu()
    {
        SceneManager.LoadScene("beerpongstartmenu");
    }
}