using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    public GameObject EndGameMenu;
    public GameObject CatchUI;
    public FPS_Controller playerCS;

    void Start()
    {
        EndGameMenu.SetActive(false);
        CatchUI.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if(playerCS.ballsThrown == BallSpawner.MAX_BALLS)
        {
            Debug.Log("Set active");
            EndGameMenu.SetActive(true);
        }
    }
}
