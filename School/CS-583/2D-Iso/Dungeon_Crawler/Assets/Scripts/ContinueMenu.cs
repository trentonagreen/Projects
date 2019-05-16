using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ContinueMenu : MonoBehaviour
{
    public void PlayLevelOne()
    {
        SceneManager.LoadScene("LevelOne");
    }
}
