using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SawBlade : Enemy
{

    [Header("Timer")]
    [SerializeField] private float StopTimer;
    private float Timer;

    [Header("Chase")]
    [SerializeField] private float ChaseStart;
    private float SpeedBoost;
    [SerializeField] private float ChargeSpeed;
    private float NormalSpeed;
    private float Stop = 0;

    
    private bool GoRight = false;

    bool IsDead = false;

    public SpriteRenderer SawbladeSprite;

    public Animator SawbladeAnimator;
    public GameObject SawBladeAreaDamager;
    public BoxCollider2D SawbladeBoxCollider;


    protected override void Start()
    {
        base.Start();
        Timer = StopTimer;
        NormalSpeed = enemySpeed;
        SpeedBoost = enemySpeed * ChargeSpeed;
        

    }


    private void Update()
    {
        //if (IsDead == false)
        //{
            StateUpdate();
            EnemyBehavior();
       // }
       // if (IsDead == true)
       // {
       //     SawbladeAnimator.SetBool("Dead", true);
       // }
    }



    private void EnemyBehavior()
    {
        switch (enemyState)
        {
            case EnemyState.IDLE:
                Idle();
                break;
            case EnemyState.AGGRO:
                Aggro();
                break;



        }
    }

    private void StateUpdate()
    {
        float DistanceFromTarget = GetDistanceFromTarget(enemyTarget.position);



        if (DistanceFromTarget <= aggroRange)
        {
            SwitchState(EnemyState.AGGRO);
        }

        else
        {
            enemySpeed = NormalSpeed;
            Timer = StopTimer;
            SwitchState(EnemyState.IDLE);
        }
        SawbladeAnimator.SetBool("Dead", false);
        SawBladeAreaDamager.GetComponent<AreaDamager>().enabled = true;
    }


    protected override void Aggro()
    {
        Timer += Time.deltaTime;
        EnemyChase(enemySpeed);
    }

    protected override void EnemyChase(float enemySpeed)
    {

        if (transform.position.x < enemyTarget.position.x && Timer >= StopTimer)
        {
            Timer = 0;
            enemySpeed = Stop;
            GoRight = true;
        }


        else if ((transform.position.x < enemyTarget.position.x) && (Timer >= ChaseStart) && (Timer < StopTimer) && (GoRight == true)) //https://forum.unity.com/threads/i-cannot-use-multiple-conditions.439290/
        {
            enemySpeed = SpeedBoost;
            enemyBody.velocity = new Vector2(enemySpeed, enemyBody.velocity.y);
            transform.localScale = new Vector2(1, 1);
            
        }


        else if (transform.position.x > enemyTarget.position.x && Timer >= StopTimer)
        {
            Timer = 0;
            enemySpeed = Stop;
            GoRight = false;
        }

        else if ((transform.position.x > enemyTarget.position.x) && (Timer >= ChaseStart) && (Timer < StopTimer) && (GoRight == false)) //https://forum.unity.com/threads/i-cannot-use-multiple-conditions.439290/
        {
            enemySpeed = SpeedBoost;
            enemyBody.velocity = new Vector2(-enemySpeed, enemyBody.velocity.y);
            transform.localScale = new Vector2(-1, 1);
        }




    }



    public void DeathAnimation()
    {
        //IsDead = true;
        SawbladeAnimator.SetBool("Dead", true);
        SawbladeBoxCollider.enabled = false;
        //this.enabled = false;
    }

    public void ActivateSprite()
    {
        SawbladeSprite.enabled = true;
        SawbladeBoxCollider.enabled = true;
    }



}
