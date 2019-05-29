using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlyMovement : MonoBehaviour
{
    Rigidbody rbDrone;
    Transform cameraT;

    public bool lockCursor;

    void Awake()
    {
        rbDrone = GetComponent<Rigidbody>();
    }

    void Start()
    {
        cameraT = Camera.main.transform;

        if(lockCursor)
        {
            Cursor.lockState = CursorLockMode.Locked;
            Cursor.visible = false;
        }
    }

    void Update()
    {
        if (Input.GetKey(KeyCode.I) || Input.GetKey(KeyCode.K))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKeyUp(KeyCode.I) || Input.GetKeyUp(KeyCode.K) || Input.GetKeyUp(KeyCode.J) || Input.GetKeyUp(KeyCode.L))
        {
            upForce = 0;
            Invoke("Freeze", .5f);
            //rbDrone.constraints = RigidbodyConstraints.FreezePositionY;
        }
        //rbDrone.constraints = RigidbodyConstraints.FreezePositionY;
        //transform.localEulerAngles = new Vector3(transform.localEulerAngles.x, Camera.main.transform.localEulerAngles.y, transform.localEulerAngles.z);
     }

    public float smoothTurnVel;
    void FixedUpdate()
    {
        FlyUpDown();
        FlyForward();
        FlyRotation();
        FlyClampValues();
        FlyLR();

        rbDrone.AddRelativeForce(Vector3.up * upForce);
        rbDrone.rotation = Quaternion.Euler(new Vector3(tiltAmountForward, currRotationY, tiltAmountSide));
        //rbDrone.rotation = Quaternion.Euler(new Vector3(rbDrone.rotation.x, currRotationY, rbDrone.rotation.z));
    }

    void Freeze()
    {
        rbDrone.constraints = RigidbodyConstraints.FreezePositionY;
    }

    public float upForce;
    void FlyUpDown() 
    {
        if (Mathf.Abs(Input.GetAxis("Vertical")) > 0.2f || Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            if (Input.GetKey(KeyCode.I) || Input.GetKey(KeyCode.K))
            {
                rbDrone.velocity = rbDrone.velocity;
            }
            if (!Input.GetKey(KeyCode.I) && !Input.GetKey(KeyCode.K) && !Input.GetKey(KeyCode.J) && !Input.GetKey(KeyCode.L))
            {
                upForce = 450;
                rbDrone.velocity = new Vector3(rbDrone.velocity.x, Mathf.Lerp(rbDrone.velocity.y, 0, Time.deltaTime * 5), rbDrone.velocity.z);
                //upForce = 281;
            }
            if (!Input.GetKey(KeyCode.I) && !Input.GetKey(KeyCode.K) && !Input.GetKey(KeyCode.J) || !Input.GetKey(KeyCode.L))
            {
                upForce = 450;
                rbDrone.velocity = new Vector3(rbDrone.velocity.x, Mathf.Lerp(rbDrone.velocity.y, 0, Time.deltaTime * 5), rbDrone.velocity.z);
                //upForce = 110;
            }
            if (Input.GetKey(KeyCode.J) || Input.GetKey(KeyCode.L))
            {
                upForce = 410;
            }
        }
        if(Mathf.Abs(Input.GetAxis("Vertical")) < 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            //upForce = 135;
            upForce = 400;
        }

        if (Input.GetKeyDown(KeyCode.I))
        {
            upForce = 450;
            if(Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
            {
                upForce = 500;
            }
        }
        else if(Input.GetKey(KeyCode.K))
        {
            upForce = -200;
        }
        else if(!Input.GetKey(KeyCode.I) && !Input.GetKey(KeyCode.K) && (Mathf.Abs(Input.GetAxis("Vertical")) < 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) < 0.2f))
        {
            upForce = 98.1f;
        }

    }

    public float moveForwardSpeed = 500;
    public float tiltAmountForward = 0f;
    public float tiltVelocityForward;
    void FlyForward()
    {    
        if (System.Math.Abs(Input.GetAxis("Vertical") - Mathf.Epsilon) > 0f)
        {
            rbDrone.AddRelativeForce(Vector3.forward * Input.GetAxis("Vertical") * moveForwardSpeed);
            tiltAmountForward = Mathf.SmoothDamp(tiltAmountForward, 20 * Input.GetAxis("Vertical"), ref tiltVelocityForward, 0.1f);
        }
    }

    public float wantRotationY;
    public float currRotationY;
    public float rotateAmountByKeys = 2.5f;
    public float rotationVelocityY;
    void FlyRotation()
    {
        if(Input.GetKey(KeyCode.J))
        {
            wantRotationY -= rotateAmountByKeys;
        }
        if(Input.GetKey(KeyCode.L))
        {
            wantRotationY += rotateAmountByKeys;
        }

        currRotationY = Mathf.SmoothDampAngle(currRotationY, cameraT.eulerAngles.y, ref rotationVelocityY, 0.1f);
    }

    public Vector3 smoothDampVelocity;
    void FlyClampValues()
    {
        if(Mathf.Abs(Input.GetAxis("Vertical")) > 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            rbDrone.velocity = Vector3.ClampMagnitude(rbDrone.velocity, Mathf.Lerp(rbDrone.velocity.magnitude, 10.0f, Time.deltaTime * 5f));
        }
        if(Mathf.Abs(Input.GetAxis("Vertical")) > 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) < 0.2f)
        {
            rbDrone.velocity = Vector3.ClampMagnitude(rbDrone.velocity, Mathf.Lerp(rbDrone.velocity.magnitude, 10.0f, Time.deltaTime * 5f));
        }
        if(Mathf.Abs(Input.GetAxis("Vertical")) < 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            rbDrone.velocity = Vector3.ClampMagnitude(rbDrone.velocity, Mathf.Lerp(rbDrone.velocity.magnitude, 5.0f, Time.deltaTime * 5f));
        }
        if(Mathf.Abs(Input.GetAxis("Vertical")) < 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) < 0.2f)
        {
            rbDrone.velocity = Vector3.SmoothDamp(rbDrone.velocity, Vector3.zero, ref smoothDampVelocity, 0.95f);
        }
    }

    public float sideMovementSpeed = 300f;
    public float tiltAmountSide;
    public float tiltVelocitySide;
    public void FlyLR()
    {
        if(Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            rbDrone.AddRelativeForce(Vector3.right * Input.GetAxis("Horizontal") * sideMovementSpeed);
            tiltAmountSide = Mathf.SmoothDamp(tiltAmountSide, -20 * Input.GetAxis("Horizontal"), ref tiltVelocitySide, 0.1f);
        }
        else
        {
            tiltAmountSide = Mathf.SmoothDamp(tiltAmountSide, 0, ref tiltVelocitySide, 0.1f);
        }
    }
}
