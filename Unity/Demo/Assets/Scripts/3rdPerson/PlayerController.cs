﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    /* TODO
     *      - Add Blink / Dash / Dodge
     *      - crouch strafe animations
     *          
     *  FINISHED
     *      - Basic Animations
     *          - Idle
     *          - Walk
     *          - Run
     *      - Hover Animations
     *      - Movement
     *      - Rotation
     *      - Camera
     *      - Strafe Camera
     *      - Strafe Rotation
     *      - Strafe Animations
     *      - Crouch
     *      - Crouch Animations
     *      - Fall Animation
     *      - Slope Check
     */

    [Header("Speed Settings")]
    public float walk_speed;
    public float run_speed;
    [SerializeField]
    private float speed;

    [Header("Jump Settings")]
    public bool jumpEnable;
    public bool hasJumped;
    public bool isGrounded;
    public float jump_force;
    public ForceMode jump_force_type;

    [Header("Crouch Settings")]
    public bool crouchEnable;
    public bool isCrouching;
    public float crouch_speed;

    [Header("Hover Settings")]
    public bool hoverEnable;
    public float hover_force;
    public float clamp_hover;
    public ForceMode hover_force_type;

    [Header("Rotate Settings")]
    public float turn_speed;
    private Vector3 dir_pos;
    private Vector3 stor_dir;

    [Header("Animation Settings")]
    public Animator anim;
    public float InputMagn;

    [Header("Slope Settings")]
    [SerializeField]
    private bool onSlope;
    public float slope_force;
    public float slope_ray_leng;

    [Header("Strafe Settings")]
    [SerializeField]
    private bool isStrafe;

    Rigidbody rb;
    Transform cam;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        cam = Camera.main.transform;
    }

    private void Update()
    {
        #region Inputs
        var hor = Input.GetAxis("Horizontal");
        var ver = Input.GetAxis("Vertical");

        #region Sprint
        if (Input.GetButton("PS4_Circle"))
        {
            speed = run_speed;
        }
        else if (hor == 0.0f && ver == 0.0f)
        {
            speed = 0;
        }
        else if(isCrouching)
        {
            speed = crouch_speed;
        }
        else
        {
            speed = walk_speed;
        }
        #endregion Sprint

        #region Hover
        if ((Input.GetButton("PS4_X")) && hoverEnable == true)
        {
            rb.useGravity = false;
            Hover(hover_force, hover_force_type);

            anim.SetBool("isHover", true);
            anim.SetBool("isGrounded", false);
            isGrounded = false;
        }
        else
        {
            rb.useGravity = true;

            anim.SetBool("isHover", false);
        }
        #endregion Hover

        #region Jump
        if ((Input.GetButton("PS4_X")) && isGrounded == true && jumpEnable == true)
        {
            Jump(jump_force, jump_force_type);

            anim.SetBool("hasJumped", true);
            anim.SetBool("isGrounded", false);
            isGrounded = false;
        }
        else
        {
            anim.SetBool("hasJumped", false);
        }
        #endregion Jump

        #region Strafe
        if (Input.GetButton("PS4_R1"))
        {
            isStrafe = true;
        }
        else
        {
            isStrafe = false;
        }
        #endregion Strafe

        #region Crouch

        if (Input.GetButtonDown("PS4_L1") && crouchEnable)
        {
            isCrouching = true;
            anim.SetBool("isCrouching", isCrouching);
        }
        if(Input.GetButtonUp("PS4_L1") && crouchEnable)
        //else
        {
            isCrouching = false;
            anim.SetBool("isCrouching", isCrouching);
        }

        #endregion Crouch

        #endregion

        #region Rotation

        Vector3 forward = cam.forward;
        Vector3 right = cam.right;

        if (!isStrafe)
        {
            dir_pos = transform.position + (right * hor) + (forward * ver);

            Vector3 dir = dir_pos - transform.position;
            dir.y = 0;

            if (hor != 0 || ver != 0)
            {
                float angle = Quaternion.Angle(transform.rotation, Quaternion.LookRotation(dir));

                if (angle != 0)
                {
                    //rb.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(dir), turn_speed * Time.deltaTime);
                    transform.rotation = Quaternion.LookRotation(dir);
                }
            }

            Vector3 ray_start = new Vector3(transform.position.x, 1, transform.position.z);
            Debug.DrawRay(ray_start, dir, Color.green);
        }
        // Force player to look in direction of camera
        else
        {
            transform.rotation = Quaternion.Euler(0, cam.eulerAngles.y, 0);
        }
        #endregion

        #region Animations
        anim.SetFloat("InputX", hor, 0.0f, Time.deltaTime * 2f);
        anim.SetFloat("InputZ", ver, 0.0f, Time.deltaTime * 2f);

        #region Idle/Walk/Run anim
        InputMagn = new Vector2(hor, ver).sqrMagnitude;
        anim.SetFloat("InputMagnitude", InputMagn, 0.0f, Time.deltaTime);
        #endregion Idle/Walk/Run anim

        #region Strafe anim
        if (!isStrafe)
        {
            anim.SetBool("isStrafe", false);
        }
        else
        {
            anim.SetBool("isStrafe", true);
        }
        #endregion Strafe anim

        #region Jump and Falling anim
        if (isGrounded)
        {
            anim.SetBool("isGrounded", true);
            anim.SetBool("hasJumped", false);
        }
        if (rb.velocity.y < -0.1)
        {
            anim.SetBool("isGrounded", false);
            isGrounded = false;
        }
        else if(onSlope && rb.velocity.y > -0.1)
        {
            anim.SetBool("onSlope", true);
        }
        else
        {
            anim.SetBool("onSlope", false);
        }

        Debug.Log(rb.velocity.y);
        anim.SetFloat("JumpVelocity", rb.velocity.y);

        #endregion Jump and Falling anim
        #endregion

    }

    private void FixedUpdate()
    {
        var hor = Input.GetAxis("Horizontal");
        var ver = Input.GetAxis("Vertical");

        #region General Movement

        Vector3 forward = cam.forward;
        Vector3 right = cam.right;

        forward.y = 0f;
        right.y = 0f;

        Vector3 direction = hor * right + ver * forward;
        direction = direction * speed * Time.deltaTime;
        rb.MovePosition(transform.position + direction);

        #endregion

        #region Slope Check
        onSlope = OnSlope();

        if (onSlope)
        {
            //rb.AddForce(Vector3.down * slope_force);
            rb.velocity = Vector3.down * slope_force;
        }
        #endregion

    }

    void Hover(float hover_force, ForceMode type)
    {
        rb.AddRelativeForce(transform.up * hover_force, type);

        // Clamps a max velocity to hover up
        rb.velocity = new Vector3(rb.velocity.x, Mathf.Clamp(rb.velocity.y, 0, clamp_hover), rb.velocity.z);
    }

    void Jump(float jump_force, ForceMode type)
    {
        rb.velocity = Vector3.zero;
        rb.AddRelativeForce(transform.up * jump_force, type);
    }

    bool OnSlope()
    {
        RaycastHit hit;

        if(Physics.Raycast(transform.position, Vector3.down, out hit, slope_ray_leng))
        {
            if(hit.normal != Vector3.up)
            {
                return true;
            }
        }

        return false;
    }

    private void OnCollisionStay(Collision collision)
    {
        if(isGrounded == false && collision.collider.tag == "Ground")
        {
            //anim.SetBool("isGrounded", true);
            isGrounded = true;
        }
    }
}
