using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStrafe : MonoBehaviour
{
    public PlayerController playerController;
    public PlayerInputManager playerInputManager;

    public bool isStrafing;

    private void Update()
    {
        if(Input.GetButton("PS4_R1") && playerInputManager.strafeEnable)
        {
            isStrafing = true;
        }
        else
        {
            isStrafing = false;
        }

    }
}
