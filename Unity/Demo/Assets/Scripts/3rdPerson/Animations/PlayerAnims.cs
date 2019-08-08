using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnims : MonoBehaviour
{

    public PlayerController playerController;
    public PlayerInputManager playerInputManager;
    public PlayerStrafe playerStrafe;
    public PlayerHover playerHover;
    public PlayerCrouch playerCrouch;

    float horizontal;
    float vertical;
    float InputMagn;

    [Header("Jump (Root Motion)")]
    public bool isJumping;
    public AnimationClip jumpClip;

    [Header("Rolling Anim (Root Motion)")]
    public bool isRolling;
    public AnimationClip roll;

    [Header("Attack Anim (Root Motion)")]
    public bool isAttacking;
    public AnimationClip attack;

    [Header("Attack Combo (Root Motion)")]
    public bool isComboAttacking;
    public int attackCount;
    public bool canAttack;

    Animator anim;

    void Start()
    {
        anim = GetComponent<Animator>();
        canAttack = true;
    }

    private void Update()
    {
        anim.SetBool("isGrounded", playerController.isGrounded);
        anim.SetFloat("JumpVelocity", playerController.rb.velocity.y);

        horizontal = playerController.hor;
        vertical = playerController.ver;

        anim.SetFloat("InputX", horizontal, 0.0f, Time.deltaTime * 2f);
        anim.SetFloat("InputZ", vertical, 0.0f, Time.deltaTime * 2f);

        #region Idle/Walk/Run Anims
        InputMagn = new Vector2(horizontal, vertical).sqrMagnitude;
        anim.SetFloat("InputMagnitude", InputMagn, 0.0f, Time.deltaTime);
        #endregion

        #region Strafe Anim
        if (playerStrafe.isStrafing)
        {
            anim.SetBool("isStrafe", true);
        }
        else
        {
            anim.SetBool("isStrafe", false);
        }
        #endregion Strafe Anim

        #region Crouch Anim
        if (playerCrouch.isCrouching)
        {
            anim.SetBool("isCrouching", true);
        }
        else
        {
            anim.SetBool("isCrouching", false);
        }
        #endregion Crouch Anim

        #region Roll (Root) Anim
        if(Input.GetButton("PS4_Square") && playerInputManager.rollEnable)
        {
            isRolling = true;
            anim.applyRootMotion = true;
            anim.SetBool("isRolling", isRolling);
            StartCoroutine(RollingAnim());
        }
        #endregion Roll Anim

        #region Jump (Root) Anim
        if(Input.GetButton("PS4_X") && playerInputManager.jumpRootEnable)
        {
            isJumping = true;
            anim.applyRootMotion = true;
            playerController.rb.useGravity = false;
            anim.SetBool("isJumpingRoot", isJumping);
            StartCoroutine(JumpingAnim());
        }
        #endregion

        #region Attack (Root) Anim
        if (Input.GetButton("PS4_Triangle") && playerInputManager.attackEnable)
        {
            isAttacking = true;
            anim.applyRootMotion = true;
            anim.SetBool("isAttacking", isAttacking);
            StartCoroutine(AttackAnim());
        }
        #endregion

        #region Combo Attack Anim 
        if (Input.GetButtonDown("PS4_Triangle") && playerInputManager.comboAttackEnable && !isRolling && !playerInputManager.isCrouching && !playerInputManager.isStrafing)
        {
            ComboStart();
        }
        #endregion

    }

    private void FixedUpdate()
    {
        //anim.SetBool("isGrounded", playerController.isGrounded);

        #region Hover 

        anim.SetBool("isHover", playerHover.isHover);

        #endregion Hover

        #region Jump
        
        #endregion Jump
    }

    private IEnumerator RollingAnim()
    {
        yield return new WaitForSeconds(roll.length);

        isRolling = false;
        anim.applyRootMotion = false;
        anim.SetBool("isRolling", isRolling);
    }

    private IEnumerator JumpingAnim()
    {
        yield return new WaitForSeconds(jumpClip.length);

        isJumping = false;
        anim.applyRootMotion = false;
        playerController.rb.useGravity = true;
        anim.SetBool("isJumpingRoot", false);
    }

    private IEnumerator AttackAnim()
    {
        yield return new WaitForSeconds(attack.length);

        isAttacking = false;
        anim.applyRootMotion = false;
        anim.SetBool("isAttacking", false);
    }

    public void ComboStart()
    {
        if (canAttack)
        {
            attackCount++;
        }

        if (attackCount == 1)
        {
            anim.SetInteger("AttackCount", 1);
            anim.applyRootMotion = true;
            isComboAttacking = true;
        }
    }

    public void ComboCheck()
    {
        canAttack = false;

        if (anim.GetCurrentAnimatorStateInfo(0).IsName("Attack Combo 1") && attackCount == 1)
        {
            anim.SetInteger("AttackCount", 0);
            canAttack = true;
            attackCount = 0;
            anim.applyRootMotion = false;
            isComboAttacking = false;
        }
        else if (anim.GetCurrentAnimatorStateInfo(0).IsName("Attack Combo 1") && attackCount >= 2)
        {
            anim.SetInteger("AttackCount", 2);
            canAttack = true;
        }
        else if (anim.GetCurrentAnimatorStateInfo(0).IsName("Attack Combo 2") && attackCount == 2)
        {
            anim.SetInteger("AttackCount", 0);
            canAttack = true;
            attackCount = 0;
            anim.applyRootMotion = false;
            isComboAttacking = false;
        }
        else if (anim.GetCurrentAnimatorStateInfo(0).IsName("Attack Combo 2") && attackCount >= 3)
        {
            anim.SetInteger("AttackCount", 3);
            canAttack = true;
        }
        else if (anim.GetCurrentAnimatorStateInfo(0).IsName("Attack Combo 3"))
        {
            anim.SetInteger("AttackCount", 0);
            canAttack = true;
            attackCount = 0;
            anim.applyRootMotion = false;
            isComboAttacking = false;
        }
        else
        {
            anim.SetInteger("AttackCount", 0);
            canAttack = true;
            attackCount = 0;
            anim.applyRootMotion = false;
            isComboAttacking = false;
        }
    }
}
