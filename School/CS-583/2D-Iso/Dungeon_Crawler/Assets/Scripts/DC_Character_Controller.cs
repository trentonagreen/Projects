using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class DC_Character_Controller : MonoBehaviour
{
    [SerializeField]
    float moveSpeed = 5f;
    [SerializeField]
    float firePower = 5f;
    [SerializeField]
    bool x;
    [SerializeField]
    bool y;
    [SerializeField]
    bool z;

    Vector3 localPosition0;

    public Animator animator;
    Vector3 vertical, horizontal;

    public float animationSpeed;

    public Rigidbody rb;

    public Transform fireBallSpawn;
    public GameObject fireballPrefab;

    public int health = 5;
    public Text healthText;

    public int flowersDestroyed = 0;

    public bool hasGem = false;
    public bool isAlive;

    public Text gameOverText;
    public Text restartLevelText;

    public AudioClip FireClip;
    public AudioSource FireSource;

    void Start()
    {
        rb = GetComponent<Rigidbody>();

        SetOriginalLocalPosition();

        vertical = Camera.main.transform.forward;
        vertical.y = 0;
        vertical = Vector3.Normalize(vertical);

        //creating rotation for vector
        horizontal = Quaternion.Euler(new Vector3(0, 90, 0)) * vertical;

        SetHealthText();
        gameOverText.text = "";
        restartLevelText.text = "";

        isAlive = true;

        FireSource.clip = FireClip;
    }


    void Update()
    {
        if(isAlive == false)
        {
            this.x = true;
            this.z = true;

            if(Input.GetKey(KeyCode.R))
            {
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
            }
        }

        rb.constraints = RigidbodyConstraints.FreezeRotation;

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

        AnimateSpeed(animationSpeed);
    }

    private void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.D))
        {
            Move();

            if(Input.GetMouseButtonDown(0) || Input.GetKeyDown(KeyCode.Space))
            {
                AttackAnimationM0();
                FireSource.Play();
                Invoke("AttackM0", .05f);
            }
        }

        else if (Input.GetMouseButtonDown(0) || Input.GetKeyDown(KeyCode.Space))
        {
            AttackAnimationM0();
            FireSource.Play();
            Invoke("AttackM0", .05f);
        }
    }

    void Move()
    {

        Vector3 direction = new Vector3(Input.GetAxis("HorizontalKey"), 0, Input.GetAxis("VerticalKey"));

        Vector3 horizontalMovement = horizontal * moveSpeed * Time.deltaTime * Input.GetAxis("HorizontalKey");
        Vector3 verticalMovement = vertical * moveSpeed * Time.deltaTime * Input.GetAxis("VerticalKey");
        Vector3 heading = Vector3.Normalize(horizontalMovement + verticalMovement);
        //Vector3 heading = horizontalMovement + verticalMovement;

        //rotation
        transform.forward = heading;

        //movement
        transform.position += horizontalMovement;
        transform.position += verticalMovement;

        //rb.AddForce((verticalMovement + horizontalMovement));
        //rb.MovePosition(transform.position + heading);

        SpriteAnimation(direction);
    }

    void AttackM0()
    {
        //Debug.Log(transform.localEulerAngles.y);
        //AttackAnimationM0();

        //Debug.Log(fireBallSpawn.transform.position);

        Vector3 adj_fireBallSpawn = new Vector3(fireBallSpawn.transform.position.x, .4f, fireBallSpawn.transform.position.z);
        Debug.Log(adj_fireBallSpawn);

        GameObject projectile = Instantiate(fireballPrefab, adj_fireBallSpawn, Quaternion.identity);
        Rigidbody projectileRB = projectile.GetComponent<Rigidbody>();
        projectileRB.velocity = transform.forward * firePower;

        //AttackAnimationM0();
    }

    void AttackM1()
    {
        Debug.Log(transform.localEulerAngles.y);
        AttackAnimationM1();
    }

    void SpriteAnimation(Vector3 direction)
    {
        // NORTH
        if ((int)direction.x == 0 && (int)direction.z == 1)
        {
            animator.SetBool("facingNorth", true);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", false);
        }
        // SOUTH
        else if ((int)direction.x == 0 && (int)direction.z == -1)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", true);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", false);
        }
        // EAST
        else if ((int)direction.x == 1 && (int)direction.z == 0)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", true);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", false);
        }
        // WEST
        else if ((int)direction.x == -1 && (int)direction.z == 0)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", true);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", false);
        }
        // NORTHEAST
        else if ((int)direction.x == 1 && (int)direction.z == 1)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", true);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", false);
        }
        // NORTHWEST
        else if ((int)direction.x == -1 && (int)direction.z == 1)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", true);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", false);
        }
        // SOUTHEAST
        else if ((int)direction.x == 1 && (int)direction.z == -1)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", true);
            animator.SetBool("facingSouthwest", false);
        }
        // SOUTHWEST
        else if ((int)direction.x == -1 && (int)direction.z == -1)
        {
            animator.SetBool("facingNorth", false);
            animator.SetBool("facingSouth", false);
            animator.SetBool("facingEast", false);
            animator.SetBool("facingWest", false);
            animator.SetBool("facingNortheast", false);
            animator.SetBool("facingNorthwest", false);
            animator.SetBool("facingSoutheast", false);
            animator.SetBool("facingSouthwest", true);
        }
    }

    void AttackAnimationM0()
    {
        // NORTH
        if ((int)transform.localEulerAngles.y == 45 || (int)transform.localEulerAngles.y == 44)
        {
            animator.SetTrigger("clickedNorthM0");
        }
        // SOUTH
        else if ((int)transform.localEulerAngles.y == 225)
        {
            animator.SetTrigger("clickedSouthM0");
        }
        // EAST
        else if ((int)transform.localEulerAngles.y == 135)
        {
            animator.SetTrigger("clickedEastM0");
        }
        // WEST
        else if ((int)transform.localEulerAngles.y == 315)
        {
            animator.SetTrigger("clickedWestM0");
        }
        // NORTHEAST
        else if ((int)transform.localEulerAngles.y == 90 || (int)transform.localEulerAngles.y == 89)
        {
            animator.SetTrigger("clickedNortheastM0");
        }
        // NORTHWEST
        else if ((int)transform.localEulerAngles.y == 0)
        {
            animator.SetTrigger("clickedNorthwestM0");
        }
        // SOUTHEAST
        else if ((int)transform.localEulerAngles.y == 180)
        {
            animator.SetTrigger("clickedSoutheastM0");
        }
        // SOUTHWEST
        else if ((int)transform.localEulerAngles.y == 270)
        {
            animator.SetTrigger("clickedSouthwestM0");
        }

    }

    void AttackAnimationM1()
    {
        // NORTH
        if ((int)transform.localEulerAngles.y == 45 || (int)transform.localEulerAngles.y == 44)
        {
            animator.SetTrigger("clickedNorthM1");
        }
        // SOUTH
        else if ((int)transform.localEulerAngles.y == 225)
        {
            animator.SetTrigger("clickedSouthM1");
        }
        // EAST
        else if ((int)transform.localEulerAngles.y == 135)
        {
            animator.SetTrigger("clickedEastM1");
        }
        // WEST
        else if ((int)transform.localEulerAngles.y == 315)
        {
            animator.SetTrigger("clickedWestM1");
        }
        // NORTHEAST
        else if ((int)transform.localEulerAngles.y == 90 || (int)transform.localEulerAngles.y == 89)
        {
            animator.SetTrigger("clickedNortheastM1");
        }
        // NORTHWEST
        else if ((int)transform.localEulerAngles.y == 0)
        {
            animator.SetTrigger("clickedNorthwestM1");
        }
        // SOUTHEAST
        else if ((int)transform.localEulerAngles.y == 180)
        {
            animator.SetTrigger("clickedSoutheastM1");
        }
        // SOUTHWEST
        else if ((int)transform.localEulerAngles.y == 270)
        {
            animator.SetTrigger("clickedSouthwestM1");
        }
    } 

    void AnimateSpeed(float animationSpeed)
    {
        animator.speed = animationSpeed;
    }

    public void SetOriginalLocalPosition()
    {
        localPosition0 = transform.localPosition;
        //Debug.Log(localPosition0);
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Gem")
        {
            hasGem = true;
            other.gameObject.SetActive(false);
        }
        if(other.gameObject.tag == "Enemy" || other.gameObject.tag == "Shock")
        {
            health--;
            SetHealthText();
        }
    }

    void SetHealthText()
    {
        healthText.text = "Health: " + health.ToString();
        if(health <= 0)
        {
            gameOverText.text = "GAME OVER";
            restartLevelText.text = "Press R to Restart Level";
            isAlive = false;
        }
    }
}
