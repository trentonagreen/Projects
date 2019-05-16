using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FPS_Controller : MonoBehaviour
{

    public AudioSource bloopSource;

    public float mouseXsensitivity = 200f;
    public float mouseYsensitivity = 200f;
    public float moveSpeed = 10f;
    public int ballsThrown = 0;
    public float throwForce = 550f;

    Transform cameraTransform;
    float verticalLookRot;
    Vector3 moveCount;
    Vector3 smoothMoveV;
    Rigidbody playerRB;

    float lockRot = 0;

    void Start()
    {
        cameraTransform = Camera.main.transform;
        playerRB = GetComponent<Rigidbody>();
        bloopSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        transform.rotation = Quaternion.Euler(lockRot, transform.rotation.eulerAngles.y, lockRot);

        transform.Rotate(Vector3.up * Input.GetAxis("Mouse X") * Time.deltaTime * mouseXsensitivity);
        verticalLookRot += Input.GetAxis("Mouse Y") * Time.deltaTime * mouseYsensitivity;
        verticalLookRot = Mathf.Clamp(verticalLookRot, -60, 60);
        cameraTransform.localEulerAngles = Vector3.left * verticalLookRot;

        Vector3 moveDir = new Vector3(Input.GetAxisRaw("Horizontal"), 0, Input.GetAxisRaw("Vertical")).normalized;
        Vector3 targetMovement = moveDir * moveSpeed;
        moveCount = Vector3.SmoothDamp(moveCount, targetMovement, ref smoothMoveV, .15f);

        playerRB.useGravity = true;
    }

    private void FixedUpdate()
    {
        playerRB.MovePosition(playerRB.position + transform.TransformDirection(moveCount) * Time.fixedDeltaTime);
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Red Solo Cup Variant") {
            bloopSource.Play();

            Destroy(collision.gameObject);

        }
    }
}
