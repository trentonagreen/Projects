using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCrouch : MonoBehaviour
{
    public PlayerController playerController;
    public PlayerInputManager playerInputManager;

    public float crouchSpeed;
    public bool isCrouching;

    void Update()
    {
        if (Input.GetButton("PS4_L1") && playerInputManager.crouchEnable)
        {
            // playerInputManager.isCrouching = true;
            isCrouching = true;
        }
        else
        {
            isCrouching = false;
        }

        if(isCrouching)
        {
            playerController.speed = crouchSpeed;
        }
    }
}
