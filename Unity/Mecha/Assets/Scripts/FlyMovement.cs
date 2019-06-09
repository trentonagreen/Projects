using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlyMovement : MonoBehaviour
{
    Rigidbody rbDrone;
    Transform cameraT;

    public bool lockCursor;
    public bool isL2Down = false;
    public bool isL2Up = true;
    public bool isR2Down = false;
    public bool isR2Up = true;

    private bool isR2;

    public KeepOriginalPos orignalPos;

    Quaternion startRot;
    Vector3 startVel;

    void Awake()
    {
        rbDrone = GetComponent<Rigidbody>();
        startRot = Quaternion.Euler(rbDrone.rotation.x, rbDrone.rotation.y, rbDrone.rotation.z);
        startVel = rbDrone.velocity;
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

        EnableButtonForL2();
        EnableButtonForR2();

        rbDrone.constraints = RigidbodyConstraints.FreezeRotationZ;

        /*
            CONTROLLER INPUT
        */

        /*
        if(Input.GetButton("PS4_L1"))
        {
            rbDrone.drag = 0;
            rbDrone.constraints = RigidbodyConstraints.None;
        }

        if(Input.GetButtonUp("PS4_L1"))
        {
            upForce = 0;
            //Invoke("FreezeY", .5f);
            FreezeY();
        }
        */

        if (Input.GetAxis("Vertical") != 0 || Input.GetAxis("Horizontal") != 0)
        {
            rbDrone.drag = 0;
            rbDrone.constraints = RigidbodyConstraints.None;
            rbDrone.constraints = RigidbodyConstraints.FreezeRotationZ;
            rbDrone.constraints = RigidbodyConstraints.FreezePositionY;
        }

        if (Input.GetAxisRaw("Vertical") == 0 && Input.GetAxisRaw("Horizontal") == 0)
        {
            //upForce = 0;
            rbDrone.drag = 10;
            Freeze();
        }

        /*
            KEYBOARD INPUT
        */
        if (Input.GetKey(KeyCode.I) || Input.GetKey(KeyCode.K) || Input.GetButton("PS4_L1") || isL2Down)
        {
            rbDrone.drag = 0;
            rbDrone.constraints = RigidbodyConstraints.None;
            rbDrone.constraints = RigidbodyConstraints.FreezeRotationZ;
        }

        if (Input.GetKeyUp(KeyCode.I) || Input.GetKeyUp(KeyCode.K) || Input.GetButtonUp("PS4_L1"))
        {
            upForce = 0;
            //Invoke("FreezeY", .5f);
            FreezeY();
        }

        /*
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.D))
        {
            rbDrone.drag = 0;
            rbDrone.constraints = RigidbodyConstraints.None;
            rbDrone.constraints = RigidbodyConstraints.FreezePositionY;
        }

        if (Input.GetKeyUp(KeyCode.W) || Input.GetKeyUp(KeyCode.A) || Input.GetKeyUp(KeyCode.S) || Input.GetKeyUp(KeyCode.D))
        //else 
        {
            upForce = 0;
            rbDrone.drag = 10;
            //Invoke("Freeze", 1f);
            Freeze();
        }

        if(Input.GetKey(KeyCode.W) && Input.GetKey(KeyCode.I))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.A) && Input.GetKey(KeyCode.I))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.S) && Input.GetKey(KeyCode.I))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.D) && Input.GetKey(KeyCode.I))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.W) && Input.GetKey(KeyCode.K))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.A) && Input.GetKey(KeyCode.K))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.S) && Input.GetKey(KeyCode.K))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        if (Input.GetKey(KeyCode.D) && Input.GetKey(KeyCode.K))
        {
            rbDrone.constraints = RigidbodyConstraints.None;
        }
        */
 
        if (Input.GetKey(KeyCode.Space) || Input.GetButton("PS4_R1"))
        {
            Fire();
        }

        //  ENABLE FOR FAST BULLET SHOOT
        if(isR2Down)
        {
            FireBig();
        }

        //Debug.Log(rbDrone.velocity);
        //rbDrone.rotation = Quaternion.Euler(new Vector3(cameraT.eulerAngles.x, currRotationY, rbDrone.rotation.z));
    }

    public float smoothTurnVel;
    void FixedUpdate()
    {
        FlyUpDown();
        FlyForward();
        FlyRotation();
        FlyClampValues();
        FlyLR();

        //rbDrone.AddRelativeForce(transform.up * upForce);
        //rbDrone.AddRelativeForce(orignalPos.orignalVectorUp * upForce);
        rbDrone.AddForce(orignalPos.orignalTransUp * upForce);

        //Vector3 movement = new Vector3(Input.GetAxis("Horizontal") * moveForwardSpeed * Time.deltaTime, 0, Input.GetAxis("Vertical") * Time.deltaTime * moveForwardSpeed);
        //rbDrone.MovePosition(transform.position + movement + transform.forward);

        //rbDrone.MovePosition(transform.position + Vector3.up * upForce * Time.deltaTime);

        //rbDrone.rotation = Quaternion.Euler(new Vector3(tiltAmountForward, currRotationY, tiltAmountSide));


        rbDrone.rotation = Quaternion.Euler(new Vector3(cameraT.eulerAngles.x, currRotationY, rbDrone.rotation.z));


        //rbDrone.rotation = Quaternion.Euler(new Vector3(rbDrone.rotation.x, currRotationY, rbDrone.rotation.z));
        //if(Input.GetKey(KeyCode.Space))
        //{
        //    Fire();
        //}
    }

    void FreezeY()
    {
        rbDrone.constraints = RigidbodyConstraints.FreezePositionY;
    }

    void Freeze()
    {
        rbDrone.constraints = RigidbodyConstraints.FreezePosition;
    }

    public float upForce;
    void FlyUpDown() 
    {
        /*
         * NEW      
         */
         /*
        rbDrone.velocity = rbDrone.velocity;
        if (Input.GetKey(KeyCode.I) || Input.GetButton("PS4_L1"))
        {
            //rbDrone.velocity = rbDrone.velocity;
            upForce = 30000;
            //if(Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
            //{
            //    upForce = 500;
            //}
        }
        else if (Input.GetKey(KeyCode.K) || isL2Down)
        {
            //rbDrone.velocity = rbDrone.velocity;
            upForce = -2000;
        }
        else
        {
            upForce = 0;
            rbDrone.velocity = new Vector3(rbDrone.velocity.x, Mathf.Lerp(rbDrone.velocity.y, 0, Time.deltaTime * 5), rbDrone.velocity.z);
        }
        */

        /*
        if (Mathf.Abs(Input.GetAxis("Vertical")) > 0.2f || Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            if (Input.GetKey(KeyCode.I) || Input.GetKey(KeyCode.K) || Input.GetButtonDown("PS4_L1") || isL2Down)
            {
                rbDrone.velocity = rbDrone.velocity;
            }
            if (!Input.GetKey(KeyCode.I) && !Input.GetKey(KeyCode.K) || !Input.GetButtonDown("PS4_L1"))
            {
                upForce = 450;
                rbDrone.velocity = new Vector3(rbDrone.velocity.x, Mathf.Lerp(rbDrone.velocity.y, 0, Time.deltaTime * 5), rbDrone.velocity.z);
                upForce = 281;
            }
        }
        if(Mathf.Abs(Input.GetAxis("Vertical")) < 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
        {
            upForce = 135;
            upForce = 400;
        }
        */
        if (Input.GetKey(KeyCode.I) || Input.GetButton("PS4_L1"))
        {
            rbDrone.velocity = rbDrone.velocity;
            upForce = 2000;
            if(Mathf.Abs(Input.GetAxis("Horizontal")) > 0.2f)
            {
                upForce = 1800;
            }
        }
        else if(Input.GetKey(KeyCode.K) || isL2Down)
        {
            rbDrone.velocity = rbDrone.velocity;
            upForce = -1000;
        }
        else if(!Input.GetKey(KeyCode.I) && !Input.GetKey(KeyCode.K) && Input.GetButtonDown("PS4_L1") && (Mathf.Abs(Input.GetAxis("Vertical")) < 0.2f && Mathf.Abs(Input.GetAxis("Horizontal")) < 0.2f))
        {
            upForce = 98.1f;
        }
        else
        {
            upForce = 0;
            rbDrone.velocity = new Vector3(rbDrone.velocity.x, Mathf.Lerp(rbDrone.velocity.y, 0, Time.deltaTime * 5), rbDrone.velocity.z);
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

            //rbDrone.MovePosition(transform.position + Vector3.forward * Input.GetAxis("Vertical") * Time.deltaTime * moveForwardSpeed);
            tiltAmountForward = Mathf.SmoothDamp(tiltAmountForward, 20 * Input.GetAxis("Vertical"), ref tiltVelocityForward, 0);
        }
    }

    public float wantRotationY;
    public float currRotationY;
    public float rotateAmountByKeys = 3.0f;
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

        //currRotationY = Mathf.SmoothDampAngle(currRotationY, cameraT.eulerAngles.y, ref rotationVelocityY, 0.2f);
        currRotationY = Mathf.SmoothDampAngle(currRotationY, cameraT.eulerAngles.y, ref rotationVelocityY, 0.3f);

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

            //rbDrone.MovePosition(transform.position + Vector3.right * Input.GetAxis("Horizontal") * Time.deltaTime * sideMovementSpeed);
            tiltAmountSide = Mathf.SmoothDamp(tiltAmountSide, -20 * Input.GetAxis("Horizontal"), ref tiltVelocitySide, 0.1f);
        }
        else
        {
            tiltAmountSide = Mathf.SmoothDamp(tiltAmountSide, 0, ref tiltVelocitySide, 0.1f);
        }
    }

    public GameObject _ammoPrefabSmall;
    public Transform _ammoSpawnPointSmall;

    public float firePower = 10f;
    public void Fire()
    {
        GameObject ammo = Instantiate(_ammoPrefabSmall, _ammoSpawnPointSmall.transform.position, Quaternion.identity) as GameObject;
        Rigidbody ammoRB = ammo.GetComponent<Rigidbody>();
        ammoRB.AddForce(transform.forward * firePower);

        //Destroy(ammo, 2f);
    }

    public GameObject _ammoPrefabBig;
    public Transform _ammoSpawnPointBig;

    public void FireBig()
    {
        GameObject ammo = Instantiate(_ammoPrefabBig, _ammoSpawnPointBig.transform.position, Quaternion.identity) as GameObject;
        Rigidbody ammoRB = ammo.GetComponent<Rigidbody>();
        ammoRB.AddForce(transform.forward * firePower);
    }

    void EnableButtonForL2()
    {
        float foo = Input.GetAxisRaw("PS4_L2");
        if (foo < 0)
        {
            if (!isL2Up) //up
            {
                isL2Up = true; //up
            }
            if (isL2Down)  //down
            {
                isL2Down = false;  //down
            }
        }
        else if (foo > 0)
        {
            if (isL2Up)
            {
                isL2Up = false;
            }
            if (!isL2Down)
            {
                isL2Down = true;
            }
        }
        else if (foo == 0)
        {
            if (isL2Up)
            {
                isL2Down = false;
            }
            if (isL2Down)
            {
                isL2Up = false;
            }
        }
    }

    void EnableButtonForR2()
    {
        float foo = Input.GetAxisRaw("PS4_R2");
        if (foo < 0)
        {
            if (!isR2Up)
            {
                isR2Up = true;
            }
            if (isR2Down)
            {
                isR2Down = false;
            }
        }
        else if (foo > 0)
        {
            if (isR2Up)
            {
                isR2Up = false;
            }
            if(!isR2Down)
            {
                // FireBig() for buttondown effect, remove for button
                //FireBig();
                isR2Down = true;
            }
        }
        else if(foo == 0)
        {
            if(isL2Up)
            {
                isR2Down = false;
            }
            if(isR2Down)
            {
                isR2Up = false;
            }
        }
    }
}
