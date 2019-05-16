using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyController : MonoBehaviour
{
    [SerializeField]
    bool x;
    [SerializeField]
    bool y;
    [SerializeField]
    bool z;

    Vector3 localPosition0;

    public DC_Character_Controller playerController;

    public Transform player;
    public float walkingDistance = 10.0f;
    public float smoothTime = 10.0f;
    private Vector3 smoothVelocity = Vector3.zero;

    private Rigidbody rb;

    Vector3 moveDirection;

    public int health = 3;
    public bool isBoss = false;

    public Transform gemSpawn;
    public GameObject gemPrefab;

    private bool spawnedGem = false;

    private void Start()
    {

        rb = GetComponent<Rigidbody>();

        SetOriginalLocalPosition();

        if(isBoss)
        {
            health = 20;
        }
    }


    void Update()
    {
        float x, y, z;

        if (this.x)
            x = localPosition0.x;
        else
            x = transform.localPosition.x;

        if (this.y)
            y = localPosition0.y;
        else
            y = transform.localPosition.y;

        if (this.z)
            z = localPosition0.z;
        else
            z = transform.localPosition.z;


        transform.localPosition = new Vector3(x, y, z);

        transform.LookAt(player);

        float distance = Vector3.Distance(transform.position, player.position);
      
        if (distance < walkingDistance)
        {
            transform.position = Vector3.SmoothDamp(transform.position, player.position, ref smoothVelocity, smoothTime);
        }

        if (health <= 0)
        {
            if (isBoss == true && spawnedGem == false)
            {
                GameObject gem = Instantiate(gemPrefab, gemSpawn.position, Quaternion.Euler(0, 45, 0));
                spawnedGem = true;
            }

            gameObject.SetActive(false);
        }

    }

    private void LateUpdate()
    {
        transform.localEulerAngles = new Vector3(0, transform.eulerAngles.y, transform.eulerAngles.z);
    }

    public void SetOriginalLocalPosition()
    {
        localPosition0 = transform.localPosition;
    }


    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Fireball")
        {
            Destroy(other.gameObject);
            health--;
        }
    }
}
