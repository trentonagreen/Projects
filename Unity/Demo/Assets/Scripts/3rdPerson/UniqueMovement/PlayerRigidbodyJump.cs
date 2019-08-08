using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerRigidbodyJump : MonoBehaviour
{
    public PlayerController playerController;
    public PlayerInputManager playerInputManager;

    [Header("Jump Settings")]
    public bool hasJumped;
    public float jumpForce;
    public ForceMode jumpForceMode;

    private void FixedUpdate()
    {
        #region Jump
        if ((Input.GetButton("PS4_X")) && playerController.isGrounded && playerInputManager.jumpEnable == true)
        {
            Jump(jumpForce, jumpForceMode);

            //anim.SetBool("hasJumped", true);
            //anim.SetBool("isGrounded", false);
        }
        else
        {
            //anim.SetBool("hasJumped", false);
        }

        if (playerController.isGrounded)
        {
            //anim.SetBool("isGrounded", true);
            //anim.SetBool("hasJumped", false);
        }
        #endregion Jump
    }

    void Jump(float jump_force, ForceMode type)
    {
        playerController.rb.velocity = Vector3.zero;
        playerController.rb.AddForce(transform.up * jump_force, type);
    }
}
