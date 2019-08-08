using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerDash : MonoBehaviour
{
    public PlayerController playerController;
    public PlayerInputManager playerInputManager;

    public bool isDashing;
    public bool canDash;
    public float dashForce;
    public float dashCoolDown;
    public float dashTimer;
    public float dashDuration;
    public float dashStart;
    public ForceMode dashForceMode;
    public GameObject dashEffect;

    public SkinnedMeshRenderer skin;
    public SkinnedMeshRenderer joint;

    Vector3 forward;
    Vector3 right;

    void Start()
    {
        dashEffect.SetActive(false);
        canDash = true;
    }

    private void FixedUpdate()
    {
        dashTimer += Time.deltaTime;

        if(dashTimer > dashCoolDown)
        {
            dashTimer = 0;
            canDash = true;
        }

        if(Input.GetButton("PS4_Square") && playerInputManager.dashEnable && canDash)
        {
            forward = playerController.cam.forward;
            right = playerController.cam.right;

            isDashing = true;
            Vector3 dashDir = playerController.hor * right + playerController.ver * forward;

            StartCoroutine(Dash(dashDir, dashForce, dashForceMode));
            canDash = false;
            dashTimer = 0;
        }
    }

    IEnumerator Dash (Vector3 direction, float force, ForceMode mode)
    {
        skin.enabled = false;
        joint.enabled = false;

        dashEffect.SetActive(true);

        playerController.rb.AddForce(direction * dashForce, mode);
        yield return new WaitForSeconds(dashDuration);

        isDashing = false;
        skin.enabled = true;
        joint.enabled = true;

        playerController.rb.velocity = Vector3.zero;
        dashEffect.SetActive(false);
    }
}
