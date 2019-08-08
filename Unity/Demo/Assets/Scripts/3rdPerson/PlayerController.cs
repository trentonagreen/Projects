using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    /* TODO
     *      - heavy attack
     *      - rotation speed
     *      - FIX RIGIDBODY JUMP
     *      
     *      - SEPERATE SCRIPT TO SMALLER ONES
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
     *      - Dash Mechanic 
     *      - Dash Animations
     *      - FIXED spinning after collision
     *      - Improved Slope Interaction
     *      - Added 1 Attack
     *      - Added Rolling
     *      - Jump Root Motion
     *      - Crouch Strafe Anims
     *      - Combo Attacks
     *      - Attack/Roll from strafe
     *      - Better Jump root anim
     *      - Best Slopes
     *      - Better Jump land animation
     */

    public bool isGrounded;

    [Header("Speed Settings")]
    public float walk_speed;
    public float run_speed;
    public float speed;

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

    [Header("Better Slope Check")]
    public LayerMask ground;
    public float maxGroundAngle = 120;
    public bool debug;
    float groundAngle;
    RaycastHit hitSlopeInfo;
    public bool isGroundSlopeCheck;
    
    public Rigidbody rb;
    public Transform cam;

    Collider m_Collider;
    Vector3 m_Size;

    Vector3 direction;
    Vector3 dir;

    public float ver;
    public float hor;
    public Vector3 forward;
    public Vector3 right;

    public PlayerInputManager playerInputManager;
    public PlayerAnims playerAnims;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        cam = Camera.main.transform;

        m_Collider = GetComponent<Collider>();
        m_Size = m_Collider.bounds.size;
    }

    private void Update()
    {
        hor = Input.GetAxis("Horizontal");
        ver = Input.GetAxis("Vertical");

        #region Speed / Sprint
        if (Input.GetButton("PS4_Circle"))
        {
            speed = run_speed;
        }
        else if (hor == 0.0f && ver == 0.0f)
        {
            speed = 0;
        }
        else if(playerInputManager.isCrouching)
        {
            speed = playerInputManager.playerCrouch.crouchSpeed;
        }
        else
        {
            speed = walk_speed;
        }
        #endregion Speed / Sprint

        #region Animations
        anim.SetFloat("InputX", hor, 0.0f, Time.deltaTime * 2f);
        anim.SetFloat("InputZ", ver, 0.0f, Time.deltaTime * 2f);

        #endregion

    }

    private void FixedUpdate()
    {
        hor = Input.GetAxis("Horizontal");
        ver = Input.GetAxis("Vertical");

        #region Slope Check
        onSlope = OnSlope();
        CalculateSlopeAngle();
        CheckSlope();
        DrawDebugLines();
        #endregion

        #region General Movement

        forward = cam.forward;
        right = cam.right;

        forward.y = 0f;
        right.y = 0f;

        direction = hor * right + ver * forward;
        direction = direction * speed * Time.deltaTime;

        if(playerAnims.isAttacking || playerAnims.isRolling || playerAnims.isComboAttacking || groundAngle >= maxGroundAngle)
        {
            direction = Vector3.zero;
        }

        if(onSlope && !playerInputManager.isStrafing)
        {
            direction = Vector3.Cross(hitSlopeInfo.normal, -transform.right);
            direction = direction * speed * Time.deltaTime;
        }

        if(onSlope && playerInputManager.isStrafing)
        {
            Vector3 tmp = Vector3.Cross(hitSlopeInfo.normal, direction);
            direction = Vector3.Cross(tmp, hitSlopeInfo.normal);
        }

        rb.MovePosition(transform.position + direction);


        #endregion

        #region Rotation
        if(!playerInputManager.isStrafing)
        {
            dir_pos = transform.position + (right * hor) + (forward * ver);

            dir = dir_pos - transform.position;
            dir.y = 0;

            if (hor != 0 || ver != 0)
            {
                float angle = Quaternion.Angle(transform.rotation, Quaternion.LookRotation(dir));

                if (angle != 0 && !playerAnims.isAttacking && !playerAnims.isRolling && !playerAnims.isComboAttacking)
                {
                    rb.MoveRotation(Quaternion.LookRotation(dir));
                }
            }
        }
        // Force player to look in direction of camera
        else
        {
            rb.MoveRotation(Quaternion.Euler(0, cam.eulerAngles.y, 0));
        }
        #endregion

        #region Inputs Physics Based

        #region Jump
        /*
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

        if(isGrounded)
        {
            anim.SetBool("isGrounded", true);
            anim.SetBool("hasJumped", false);
        }
        */
        #endregion Jump

        #endregion

    }

    #region Jump Function
    /*
    void Jump(float jump_force, ForceMode type)
    {
        rb.velocity = Vector3.zero;
        rb.AddRelativeForce(transform.up * jump_force, type);
    }
    */
    #endregion

    #region Collision Functions

    private void OnCollisionEnter(Collision collision)
    {
        // stops rigidbody from spinning after collision
        if (collision.collider.tag == "Ground")
        {
            rb.angularVelocity = Vector3.zero;
            rb.velocity = Vector3.zero;
        }

    }

    private void OnCollisionStay(Collision collision)
    {
        if(isGrounded == false && collision.collider.tag == "Ground")
        {
            //anim.SetBool("isGrounded", true);
            isGrounded = true;
            rb.angularVelocity = Vector3.zero;
            rb.velocity = Vector3.zero;
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        if(collision.collider.tag == "Ground")
        {
            isGrounded = false;
            rb.angularVelocity = Vector3.zero;
            rb.velocity = Vector3.zero;
        }
    }

    #endregion

    #region Better Slope Check

    bool OnSlope()
    {
        RaycastHit hit;

        if (Physics.Raycast(transform.position, Vector3.down, out hit, m_Size.y))
        {
            if (hit.normal != Vector3.up)
            {
                return true;
            }
        }

        return false;
    }

    void CalculateForwardRay()
    {
        if (!onSlope)
        {
            //direction = transform.forward;
        }
        else {
            direction = Vector3.Cross(hitSlopeInfo.normal, -transform.right);
        }
           
    }

    void CalculateSlopeAngle()
    {
        if(onSlope)
        {
            groundAngle = Vector3.Angle(hitSlopeInfo.normal, transform.forward);
        }
            
    }

    void CheckSlope()
    {
        if(Physics.Raycast(transform.position, -Vector3.up * 2, out hitSlopeInfo, m_Size.y, ground))
        {
            //isGroundSlopeCheck = true;
        }
        else
        {
            //isGroundSlopeCheck = false;
        }
    }

    void DrawDebugLines()
    {
        if(debug)
        {
            Debug.DrawLine(transform.position, transform.position + direction * m_Size.y * 10, Color.blue);
            Debug.DrawLine(transform.position, transform.position - Vector3.up * m_Size.y, Color.green);
        }
    }

    #endregion
}
