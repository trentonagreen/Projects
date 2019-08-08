using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInputManager : MonoBehaviour
{
    [Header("Enable | Disable")]
    public bool attackEnable;
    public bool comboAttackEnable;
    public bool crouchEnable;
    public bool dashEnable;
    public bool hoverEnable;
    public bool jumpEnable;
    public bool jumpRootEnable;
    public bool rollEnable;
    public bool strafeEnable;

    #region Crouch
    public bool isCrouching;
    #endregion Crouch

    #region Strafe
    public bool isStrafing;
    #endregion Strafe

    #region Dash
    public bool isDashing;
    #endregion Dash

    public PlayerStrafe playerStrafe;
    public PlayerDash playerDash;
    public PlayerCrouch playerCrouch;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        isStrafing = playerStrafe.isStrafing;
        isDashing = playerDash.isDashing;
        isCrouching = playerCrouch.isCrouching;
    }
}
