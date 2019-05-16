using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public Transform gemSpawn;
    public GameObject gemPrefab;

    public AudioClip MusicClip;
    public AudioSource MusicSource;

    private bool spawnedGem = false;

    public DC_Character_Controller playerController;

    private void Start()
    {
        MusicSource.clip = MusicClip;
        MusicSource.Play();
    }

    private void Update()
    {
        if(playerController.flowersDestroyed == 21 && spawnedGem == false)
        {
            GameObject gem = Instantiate(gemPrefab, gemSpawn.position, Quaternion.identity);
            spawnedGem = true;
        }
    }
}
