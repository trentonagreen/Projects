using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    /* TODO
     *      - Add Strafing
     *      - Add Blink / Dash / Dodge
     *      - Add Animations
     *          - Float
     *          
     *          
     *  FINISHED
     *      - Basic Animations
     *          - Idle
     *          - Walk
     *          - Run
     *      - Movement
     *      - Rotation
     *      - Camera
     */

    [Header("Speed Settings")]
    public float walk_speed;
    public float run_speed;
    [SerializeField]
    private float speed;

    [Header("Hover Settings")]
    public float hover_force;
    public float clamp_hover;
    public ForceMode force_type;

    [Header("Rotate Settings")]
    public float turn_speed;
    private Vector3 dir_pos;
    private Vector3 stor_dir;

    [Header("Animation Settings")]
    public Animator anim;
    public float InputMagn;

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

        // Sprint
        if (Input.GetButton("PS4_Circle"))
        {
            speed = run_speed;
        }
        else if (hor == 0.0f && ver == 0.0f)
        {
            speed = 0;
        }
        else
        {
            speed = walk_speed;
        }

        // Hover
        if ((Input.GetButton("PS4_L1")))
        {
            rb.useGravity = false;
            Hover(hover_force, force_type);
        }
        else
        {
            rb.useGravity = true;
        }
        #endregion

        #region Animations
        anim.SetFloat("InputX", hor, 0.0f, Time.deltaTime * 2f);
        anim.SetFloat("InputZ", ver, 0.0f, Time.deltaTime * 2f);

        InputMagn = new Vector2(hor, ver).sqrMagnitude;

        //if(anim_speed > allow_rotation)
        //{
            anim.SetFloat("InputMagnitude", InputMagn, 0.0f, Time.deltaTime);
        //}
        //else
        //{
            //anim.SetFloat("InputMagnitude", anim_speed, 0.0f, Time.deltaTime);
        //}
        #endregion
    }

    private void FixedUpdate()
    {
        #region Movement
        var hor = Input.GetAxis("Horizontal");
        var ver = Input.GetAxis("Vertical");

        /*
        Vector3 direction = new Vector3(hor, 0, ver);
        direction = direction.normalized * speed * Time.deltaTime;

        rb.MovePosition(transform.position + direction);
        */

        Vector3 forward = cam.transform.forward;
        Vector3 right = cam.transform.right;

        forward.y = 0f;
        right.y = 0f;

        Vector3 direction = hor * right + ver * forward;
        //Vector3 norm_direction = direction.normalized * speed * Time.deltaTime;
        direction = direction * speed * Time.deltaTime;
        rb.MovePosition(transform.position + direction);

        #endregion

        #region Rotation
        stor_dir = cam.right;
        dir_pos = transform.position + (stor_dir * hor) + (cam.forward * ver);

        Vector3 dir = dir_pos - transform.position;
        dir.y = 0;

        if(hor != 0 || ver != 0)
        {
            float angle = Quaternion.Angle(transform.rotation, Quaternion.LookRotation(dir));

            if(angle != 0)
            {
                rb.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(dir), turn_speed * Time.deltaTime);
            }
        }

        Debug.DrawRay(transform.position, direction, Color.red);
        #endregion
    }


    void Hover(float hover_force, ForceMode type)
    {
        rb.AddRelativeForce(transform.up * hover_force, type);

        // Clamps a max velocity to hover up
        rb.velocity = new Vector3(rb.velocity.x, Mathf.Clamp(rb.velocity.y, 0, clamp_hover), rb.velocity.z);
    }

}
