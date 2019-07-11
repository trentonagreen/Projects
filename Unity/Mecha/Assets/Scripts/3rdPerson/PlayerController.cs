using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    /* TODO
     *      - Add Strafing
     *      - Add Blink / Dash / Dodge
     *      - Add Animations
     *          - Idle
     *          - Walk
     *          - Run
     * 
     */

    [Header("Speed Settings")]
    public float walk_speed;
    public float run_speed;
    private float speed;

    [Header("Hover Settings")]
    public float hover_force;
    public float clamp_hover;
    public ForceMode force_type;

    [Header("Rotate Settings")]
    public float turn_speed;
    private Vector3 dir_pos;
    private Vector3 stor_dir;

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

        // Sprint
        if (Input.GetButton("PS4_Circle") || Input.GetKey(KeyCode.LeftShift))
        {
            speed = run_speed;
        }
        else if (speed != walk_speed)
        {
            speed = walk_speed;
        }

        // Hover
        if((Input.GetButton("PS4_L1")))
        {
            rb.useGravity = false;
            Hover(hover_force, force_type);
        }
        else
        {
            rb.useGravity = true;
        }
        #endregion
    }

    private void FixedUpdate()
    {
        #region Movement
        var hor = Input.GetAxis("Horizontal");
        var ver = Input.GetAxis("Vertical");

        Vector3 direction = new Vector3(hor, 0, ver);
        direction = direction.normalized * speed * Time.deltaTime;

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

        Debug.DrawRay(transform.position, dir, Color.red);
        #endregion
    }


    void Hover(float hover_force, ForceMode type)
    {
        rb.AddRelativeForce(transform.up * hover_force, type);

        // Clamps a max velocity to hover up
        rb.velocity = new Vector3(rb.velocity.x, Mathf.Clamp(rb.velocity.y, 0, clamp_hover), rb.velocity.z);
    }

}
