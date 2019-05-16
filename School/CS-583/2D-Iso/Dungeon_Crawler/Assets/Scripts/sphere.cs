using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class sphere : MonoBehaviour
{
    public float moveSpeed;
    private Rigidbody rb;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void FixedUpdate()
    {
        Move();
    }

    void Move()
    {
        float hAxis = Input.GetAxis("HorizontalKey");
        float vAxis = Input.GetAxis("VerticalKey");

        Vector3 move = new Vector3(hAxis, 0, vAxis) * moveSpeed * Time.deltaTime;

        rb.MovePosition(transform.position + move);
    }
}
