using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HideCursor : MonoBehaviour
{
    FPS_Controller playerCS;
    // Start is called before the first frame update
    void Start()
    {
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;

        playerCS = GameObject.FindWithTag("Player").GetComponent<FPS_Controller>();
    }

    private void Update()
    {
        if(playerCS.ballsThrown == BallSpawner.MAX_BALLS)
        {
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;

            print("start menu");
        }
    }

}
