using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RocketBot : Enemy
{
    [Header("Rocket")]
    [SerializeField] private Transform RocketFiredHere;
    [SerializeField] private GameObject Rocket;

    [Header("Leap")]
    [SerializeField] private float LeapCooldown;
    [SerializeField] private float XForce;
    [SerializeField] private float YForce;
    private float Timer;
    private float ChaseStart = 1;
    [SerializeField] private GameObject Rocketeer;

    [Header("Animation")]
    public Animator RocketeerAnimator;
    
    private bool ActivateJump;
    private bool IsDead;
    bool AnimationDead = false;
    protected override void Start()
    {
        base.Start();
        Timer = LeapCooldown;
        attackTimer = 100;
        ActivateJump = false;
        IsDead = false;

    }


    private void Update()
    {
       // if (AnimationDead == false)
       // {
            StateUpdate();
            EnemyBehavior();
            Leap();
            if (ActivateJump == true)
            {
                Timer += Time.deltaTime;
            }
       // }

       // if (AnimationDead == true)
       // {
       //     RocketeerAnimator.SetTrigger("Death");
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
            case EnemyState.ATTACK:
                Attack();
                break;


        }
    }

    private void StateUpdate()
    {
        float DistanceFromTarget = GetDistanceFromTarget(enemyTarget.position);


        if (DistanceFromTarget <= attackRange && DistanceFromTarget > aggroRange && HasLineOfSight())
        {
            if (transform.position.x < enemyTarget.position.x) //ref pelumi code above
            {
                transform.localScale = new Vector2(1, 1);
            }

            if (transform.position.x > enemyTarget.position.x)
            {
                transform.localScale = new Vector2(-1, 1);
            }


            SwitchState(EnemyState.ATTACK);
        }


        else if (DistanceFromTarget <= aggroRange && HasLineOfSight())
        {
            SwitchState(EnemyState.AGGRO);
        }


        else
        {
            SwitchState(EnemyState.IDLE);
        }

    }

    protected override void EnemyChase(float enemySpeed)
    {

        if (transform.position.x < enemyTarget.position.x && Timer >= LeapCooldown)
        {
           
            Timer = 0;
            enemyBody.AddForce(new Vector2(XForce, YForce), ForceMode2D.Impulse);
        }


        else if (transform.position.x > enemyTarget.position.x && Timer >= LeapCooldown)
        {
            
            Timer = 0;
            enemyBody.AddForce(new Vector2(-XForce, YForce), ForceMode2D.Impulse);
        }

        if ((Timer >= ChaseStart) && (Timer < LeapCooldown))
        {
            Explosion();
        } //After landing, trigger explosion



    }


    public void Leap()
    {
        if (ActivateJump == true)
        {
            EnemyChase(enemySpeed);
        }
    }


    protected override void Aggro()
    {
        ActivateJump = true;

    }

    protected override void AttackLogic()
    {
        StartCoroutine(Fire());
    }

    public void DeathAnimation()
    {
        //AnimationDead = true;
        RocketeerAnimator.SetTrigger("Death");
        IsDead = true;
        //this.enabled = false;
    }

    public void Explosion() 
    {
        AreaDamager areaDamager = GetComponent<AreaDamager>();
        areaDamager.Attack();
        DoExplosionEffect(0.3f, this.transform);
        ActivateJump = false;
        Rocketeer.SetActive(false);
    }

    IEnumerator Fire()
    {
        RocketeerAnimator.SetTrigger("Shoot");
        yield return new WaitForSeconds(0.9f);

        if ((PlayerController.Instance.transform.position.x > transform.position.x) && (IsDead == false))
        {
            Instantiate(Rocket, RocketFiredHere.position, Quaternion.Euler(0, 0, 0));
        }
        else
        {
            if (IsDead == false)
            {
                Instantiate(Rocket, RocketFiredHere.position, Quaternion.Euler(0, 0, 195));
            }
        }

        if (transform.position.x < enemyTarget.position.x) //ref pelumi code above
        {
            transform.localScale = new Vector2(1, 1);
        }

        if (transform.position.x > enemyTarget.position.x)
        {
            transform.localScale = new Vector2(-1, 1);
        }
    }

}
