using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHover : MonoBehaviour
{
    public PlayerController playerController;
    public PlayerInputManager playerInputManager;

    public float hoverForce;
    public float clampHoverForce;
    public ForceMode hoverForceMode;
    public bool isHover;

    private void FixedUpdate()
    {
        if (Input.GetButton("PS4_X") && playerInputManager.hoverEnable)
        {
            playerController.rb.useGravity = false;
            Hover(hoverForce, hoverForceMode);

            isHover = true;

            playerController.isGrounded = false;
        }
        else
        {
            playerController.rb.useGravity = true;
            isHover = false;
        }
    }

    void Hover(float force, ForceMode mode)
    {
        playerController.rb.AddRelativeForce(transform.up * force, mode);

        playerController.rb.velocity = new Vector3(playerController.rb.velocity.x, Mathf.Clamp(playerController.rb.velocity.y, 0, clampHoverForce), playerController.rb.velocity.z);
    }
}
