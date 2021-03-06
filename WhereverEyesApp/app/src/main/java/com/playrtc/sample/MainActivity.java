package com.playrtc.sample;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

/**
 * PlayRTC Sample을 구동하기 위한 Main Menu Activity
 * BaseActivity 상속 하여 구현
 */
public class MainActivity extends Activity {
    private static final int LAUNCHED_PLAYRTC = 100;
    /**
     * isCloesActivity가 false이면 Dialog를 통해 사용자의 종료 의사를 확인하고<br>
     * Activity를 종료 처리.
     */
    private boolean isCloesActivity = false;
    public static myPhoneNumber myPhone;
    LinearLayout layout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        layout=(LinearLayout)findViewById(R.id.main_layout);
        layout.setBackgroundResource(R.drawable.main);

        myPhone = new myPhoneNumber(MainActivity.this);


        // 버튼 이벤트 등록
        initUIControls();
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == LAUNCHED_PLAYRTC) {
            if (resultCode == RESULT_OK) {
            }
        }
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    protected void onDestroy() {
        android.os.Process.killProcess(android.os.Process.myPid());
        super.onDestroy();
    }

    /**
     * isCloesActivity가 false이면 Dialog를 통해 사용자의 종료 의사를 확인하고<br>
     * Activity를 종료 처리.
     */
    @Override
    public void onBackPressed() {
        // isCloesActivity가 true이면 Activity를 종료 처리.
        if (isCloesActivity) {
            super.onBackPressed();
        }
        // isCloesActivity가 false이면 Dialog를 통해 사용자의 종료 의사를 확인
        else {
            AlertDialog.Builder alert = new AlertDialog.Builder(this);
            alert.setTitle("PlayRTC Sample");
            alert.setMessage("PlatRTC Sample App을 종료하겠습니까?");

            alert.setPositiveButton("종료", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                    isCloesActivity = true;
                    onBackPressed();
                }
            });
            alert.setNegativeButton("취소", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int whichButton) {
                    dialog.dismiss();
                    isCloesActivity = false;

                }
            });
            alert.show();
        }
    }

    /**
     * Sample Type 별 버튼 이벤트 등록
     */
    private void initUIControls() {
        // 영상 + 음성 + Data Sample
        this.findViewById(R.id.btn_go_sample1).setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                goPlayRTC(1);
            }
        });this.findViewById(R.id.btn_go_camera).setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                goPlayRTC(2);
            }
        });
    }

    /**
     * PlayRTCActivity 이동
     *
     * @param type
     */
    private void goPlayRTC(int type) {
        Intent intent = new Intent(MainActivity.this, PlayRTCActivity.class);
        // PlayRTC Sample 유형 전달
        intent.putExtra("type", type);
        MainActivity.this.startActivityForResult(intent, LAUNCHED_PLAYRTC);
    }
    public class myPhoneNumber{
        Context my_context;
        public String myPhoneNum;

        public myPhoneNumber(Context ctx)
        {
            TelephonyManager telManager=(TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
            myPhoneNum=telManager.getLine1Number();
        }
        public String getMyphoneNum()
        {
            return myPhoneNum;
        }

    }

}



